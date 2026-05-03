/**
 * script.js — Final Project
 * ==========================
 * Build your JavaScript here.
 * * Requirements:
 * - Use const/let (no var)
 * - At least one async/await fetch call with try/catch
 * - At least one use of localStorage
 * - Modular: break code into named functions
 * - No alert() for user messages
 */

console.log('Final project script loaded. Time to build something great! 🚀');

// --- Weather Dashboard Logic ---

// State Variables
let isCelsius = true;
let recentSearches = JSON.parse(localStorage.getItem('weatherSearches')) || [];
let currentWeatherData = null; 

// DOM Elements
const searchForm = document.getElementById('search-form');
const cityInput = document.getElementById('city-input');
const unitToggleBtn = document.getElementById('unit-toggle');
const recentSearchesContainer = document.getElementById('recent-searches');
const statusMessage = document.getElementById('status-message');
const weatherDashboard = document.getElementById('weather-dashboard');
const currentWeatherContainer = document.getElementById('current-weather');
const forecastContainer = document.getElementById('forecast-container');

// Initialization
function init() {
    renderRecentSearches();
    if (recentSearches.length > 0) {
        fetchWeatherData(recentSearches[0]);
    }
}

// Event Listeners
searchForm.addEventListener('submit', (e) => {
    e.preventDefault();
    const city = cityInput.value.trim();
    if (city) {
        fetchWeatherData(city);
        cityInput.value = '';
    }
});

unitToggleBtn.addEventListener('click', () => {
    isCelsius = !isCelsius;
    if (currentWeatherData) {
        renderWeather(currentWeatherData.cityName, currentWeatherData.data);
    }
});

// API Calls
async function fetchWeatherData(city) {
    displayStatus('Loading weather data...', 'info');
    weatherDashboard.style.display = 'none';

    try {
        // Step 1: Geocoding
        const geoRes = await fetch(`https://geocoding-api.open-meteo.com/v1/search?name=${encodeURIComponent(city)}&count=1`);
        if (!geoRes.ok) throw new Error('Geocoding service unavailable.');
        
        const geoData = await geoRes.json();
        if (!geoData.results || geoData.results.length === 0) {
            throw new Error(`City "${city}" not found.`);
        }

        const { latitude, longitude, name } = geoData.results[0];

        // Step 2: Weather Data
        const weatherRes = await fetch(`https://api.open-meteo.com/v1/forecast?latitude=${latitude}&longitude=${longitude}&daily=temperature_2m_max,temperature_2m_min,weathercode&current_weather=true&timezone=auto`);
        if (!weatherRes.ok) throw new Error('Weather service unavailable.');
        
        const weatherData = await weatherRes.json();

        // State Update & Render
        currentWeatherData = { cityName: name, data: weatherData };
        saveSearchHistory(name);
        renderWeather(name, weatherData);
        hideStatus();

    } catch (error) {
        displayStatus(error.message, 'error');
    }
}

// LocalStorage Management
function saveSearchHistory(city) {
    if (!recentSearches.includes(city)) {
        recentSearches.unshift(city);
        if (recentSearches.length > 5) recentSearches.pop(); 
        localStorage.setItem('weatherSearches', JSON.stringify(recentSearches));
        renderRecentSearches();
    }
}

function renderRecentSearches() {
    recentSearchesContainer.innerHTML = '';
    recentSearches.forEach(city => {
        const chip = document.createElement('button');
        chip.textContent = city;
        chip.style.padding = '0.3rem 0.8rem';
        chip.style.borderRadius = '20px';
        chip.style.border = '1px solid #ccc';
        chip.style.background = '#eee';
        chip.style.cursor = 'pointer';
        chip.addEventListener('click', () => fetchWeatherData(city));
        recentSearchesContainer.appendChild(chip);
    });
}

// Utilities
function convertTemp(celsiusValue) {
    if (isCelsius) return `${Math.round(celsiusValue)}°C`;
    return `${Math.round((celsiusValue * 9/5) + 32)}°F`;
}

function getWeatherIcon(code) {
    const wmoCodes = {
        0: '☀️', 1: '🌤️', 2: '⛅', 3: '☁️',
        45: '🌫️', 48: '🌫️',
        51: '🌦️', 53: '🌧️', 55: '🌧️',
        61: '🌧️', 63: '🌧️', 65: '🌧️',
        71: '🌨️', 73: '❄️', 75: '❄️',
        80: '🌧️', 81: '🌧️', 82: '⛈️',
        95: '⛈️', 96: '⛈️', 99: '⛈️'
    };
    return wmoCodes[code] || '🌡️';
}

// UI Rendering
function renderWeather(cityName, data) {
    weatherDashboard.style.display = 'block';

    const current = data.current_weather;
    currentWeatherContainer.innerHTML = `
        <h3 style="margin: 0 0 1rem 0; font-size: 1.5rem;">${cityName}</h3>
        <div style="font-size: 3rem; margin-bottom: 1rem;">
            ${getWeatherIcon(current.weathercode)} ${convertTemp(current.temperature)}
        </div>
        <p style="margin: 0;">Wind Speed: ${current.windspeed} km/h</p>
    `;

    forecastContainer.innerHTML = '';
    const daily = data.daily;
    
    for (let i = 0; i < daily.time.length; i++) {
        const dateObj = new Date(daily.time[i]);
        const dateStr = dateObj.toLocaleDateString(undefined, { weekday: 'short', month: 'short', day: 'numeric' });
        
        const card = document.createElement('div');
        card.style.flex = '0 0 auto';
        card.style.padding = '1rem';
        card.style.border = '1px solid #ddd';
        card.style.borderRadius = '8px';
        card.style.minWidth = '100px';
        card.style.textAlign = 'center';
        
        card.innerHTML = `
            <p style="margin: 0 0 0.5rem 0; font-weight: bold;">${dateStr}</p>
            <div style="font-size: 2rem; margin-bottom: 0.5rem;">${getWeatherIcon(daily.weathercode[i])}</div>
            <div style="font-size: 0.9rem;">
                <strong>${convertTemp(daily.temperature_2m_max[i])}</strong><br>
                <span style="color: #666;">${convertTemp(daily.temperature_2m_min[i])}</span>
            </div>
        `;
        forecastContainer.appendChild(card);
    }
}

function displayStatus(message, type) {
    statusMessage.textContent = message;
    statusMessage.style.display = 'block';
    statusMessage.style.color = type === 'error' ? '#d9534f' : '#333';
}

function hideStatus() {
    statusMessage.style.display = 'none';
}

// Boot up
init();