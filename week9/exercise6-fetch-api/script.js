/**
 * Exercise 6: Fetch & APIs
 * =========================
 * Complete each async function below.
 * All APIs used are free and require no authentication.
 */

// ============================================================
// UTILITY: Show a loading spinner inside an element
// ============================================================
function showLoading(element) {
  element.innerHTML = '<div class="spinner"></div>';
}

function showError(element, message) {
  element.innerHTML = `<p class="error-text">❌ ${message}</p>`;
}


// ============================================================
// TASK 1 — Random Quote
// API: https://api.quotable.io/random
// ============================================================
const quoteDisplay = document.querySelector('#quote-display');
const btnNewQuote  = document.querySelector('#btn-new-quote');

async function fetchQuote() {
  if (!quoteDisplay) return;
  showLoading(quoteDisplay);

  try {
    // TODO: fetch from 'https://api.quotable.io/random'
    const response = await fetch('https://api.quotable.io/quotes/random');
    
    // TODO: check response.ok, throw if not
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    
    // TODO: parse JSON
    // Note: The new /quotes/random endpoint returns an array with one object
    const dataArray = await response.json();
    const data = dataArray[0];
    
    // TODO: update quoteDisplay with the quote content and author
    quoteDisplay.innerHTML = `
      <blockquote>"${data.content}"</blockquote>
      <p class="quote-author">— ${data.author}</p>
    `;

  } catch (error) {
    showError(quoteDisplay, 'Could not load quote. Check your connection.');
    console.error(error);
  }
}

// Fetch a quote when the page loads, and on button click
fetchQuote();
if (btnNewQuote) btnNewQuote.addEventListener('click', fetchQuote);


// ============================================================
// TASK 2 — GitHub User Search
// API: https://api.github.com/users/{username}
// ============================================================
const githubInput  = document.querySelector('#github-input');
const btnSearch    = document.querySelector('#btn-search-user');
const githubResult = document.querySelector('#github-result');

async function searchUser() {
  if (!githubInput || !githubResult) return;
  const username = githubInput.value.trim();
  if (!username) return;

  showLoading(githubResult);

  try {
    // TODO: fetch from `https://api.github.com/users/${username}`
    const response = await fetch(`https://api.github.com/users/${username}`);
    
    // TODO: If response.status === 404, show "User not found"
    if (response.status === 404) {
      showError(githubResult, `User "${username}" not found.`);
      return;
    }
    
    // TODO: If !response.ok for other reasons, throw an error
    if (!response.ok) {
      throw new Error(`API returned status ${response.status}`);
    }
    
    // TODO: Parse JSON and display:
    const user = await response.json();
    
    githubResult.innerHTML = `
      <div class="github-profile">
        <img src="${user.avatar_url}" alt="${user.login}'s avatar" style="width:100px; height:100px; border-radius:50%;">
        <h3>${user.name || user.login} (@${user.login})</h3>
        ${user.bio ? `<p><em>${user.bio}</em></p>` : ''}
        <p><strong>Followers:</strong> ${user.followers} | <strong>Public Repos:</strong> ${user.public_repos}</p>
        <a href="${user.html_url}" target="_blank" rel="noopener noreferrer">View on GitHub</a>
      </div>
    `;

  } catch (error) {
    showError(githubResult, error.message || 'Search failed. Try again.');
  }
}

if (btnSearch) btnSearch.addEventListener('click', searchUser);
if (githubInput) {
  githubInput.addEventListener('keydown', (e) => { 
    if (e.key === 'Enter') searchUser(); 
  });
}


// ============================================================
// TASK 3 — Posts Feed with Pagination
// API: https://jsonplaceholder.typicode.com/posts
// ============================================================
const postsContainer = document.querySelector('#posts-container');
const btnLoadMore    = document.querySelector('#btn-load-more');
let currentPage = 1;
const postsPerPage = 10;

async function loadPosts() {
  if (!postsContainer) return;
  const start = (currentPage - 1) * postsPerPage;
  
  // Show loading indicator
  const loadingDiv = document.createElement('div');
  showLoading(loadingDiv);
  postsContainer.appendChild(loadingDiv);

  try {
    // TODO: fetch from: `https://jsonplaceholder.typicode.com/posts?_start=${start}&_limit=${postsPerPage}`
    const response = await fetch(`https://jsonplaceholder.typicode.com/posts?_start=${start}&_limit=${postsPerPage}`);
    
    if (!response.ok) throw new Error('Failed to load posts');
    
    const posts = await response.json();
    
    // Remove loading indicator
    loadingDiv.remove();
    
    // TODO: For each post, create a card element and append to postsContainer
    posts.forEach(post => {
      const card = document.createElement('div');
      card.className = 'post-card card';
      card.innerHTML = `
        <h3>${post.title}</h3>
        <p>${post.body}</p>
        <button class="btn-comments" data-post-id="${post.id}">Load Comments</button>
        <div class="comments-section" id="comments-${post.id}" style="display: none; margin-top: 10px; border-top: 1px solid #ddd; padding-top: 10px;"></div>
      `;
      
      // TODO: When a card is clicked, call loadComments(post.id, cardElement)
      const btnComments = card.querySelector('.btn-comments');
      btnComments.addEventListener('click', () => loadComments(post.id, card));
      
      postsContainer.appendChild(card);
    });

    // TODO: Increment currentPage after success
    currentPage++;
    
    // Disable load more button if fewer than postsPerPage returned
    if (posts.length < postsPerPage && btnLoadMore) {
      btnLoadMore.disabled = true;
      btnLoadMore.textContent = "No more posts";
    }

  } catch (error) {
    loadingDiv.remove();
    const errorDiv = document.createElement('div');
    showError(errorDiv, 'Failed to load posts.');
    postsContainer.appendChild(errorDiv);
  }
}

async function loadComments(postId, cardElement) {
  const commentsSection = cardElement.querySelector(`#comments-${postId}`);
  const btn = cardElement.querySelector('.btn-comments');
  
  // Toggle: if comments already shown, hide them
  if (commentsSection.style.display === 'block') {
    commentsSection.style.display = 'none';
    btn.textContent = 'Load Comments';
    return;
  }
  
  // If comments are already loaded but hidden, just show them
  if (commentsSection.hasChildNodes() && !commentsSection.querySelector('.spinner')) {
    commentsSection.style.display = 'block';
    btn.textContent = 'Hide Comments';
    return;
  }

  commentsSection.style.display = 'block';
  showLoading(commentsSection);

  try {
    // TODO: fetch from `https://jsonplaceholder.typicode.com/posts/${postId}/comments`
    const response = await fetch(`https://jsonplaceholder.typicode.com/posts/${postId}/comments`);
    if (!response.ok) throw new Error('Failed to load comments');
    
    const comments = await response.json();
    
    // TODO: Display comments inside or below cardElement
    commentsSection.innerHTML = comments.map(comment => `
      <div style="margin-bottom: 8px; font-size: 0.9em;">
        <strong>${comment.email}:</strong> ${comment.body}
      </div>
    `).join('');
    
    btn.textContent = 'Hide Comments';

  } catch (error) {
    showError(commentsSection, 'Could not load comments.');
  }
}

// Initial load
loadPosts();
if (btnLoadMore) btnLoadMore.addEventListener('click', loadPosts);


// ============================================================
// TASK 5 — Promise.all: Parallel Fetches
// ============================================================
const btnFetchAll  = document.querySelector('#btn-fetch-all');
const multiResult  = document.querySelector('#multi-result');

async function fetchAllParallel() {
  if (!multiResult) return;
  showLoading(multiResult);

  try {
    // TODO: Use Promise.all to fetch all three simultaneously:
    const [quoteRes, userRes, todoRes] = await Promise.all([
      fetch('https://api.quotable.io/quotes/random'), // Using updated endpoint
      fetch('https://jsonplaceholder.typicode.com/users/1'),
      fetch('https://jsonplaceholder.typicode.com/todos/1')
    ]);
    
    if (!quoteRes.ok || !userRes.ok || !todoRes.ok) {
      throw new Error('One of the APIs failed');
    }

    const [quoteData, user, todo] = await Promise.all([
      quoteRes.json(),
      userRes.json(),
      todoRes.json()
    ]);
    
    // Extract quote from array
    const quote = quoteData[0];

    // TODO: Display all three results in multiResult
    multiResult.innerHTML = `
      <div style="display: grid; gap: 10px;">
        <div style="background:#f8f9fa; padding:10px; border-radius:5px;">
          <h4>1. Random Quote</h4>
          <p>"${quote.content}" — ${quote.author}</p>
        </div>
        <div style="background:#eef7ee; padding:10px; border-radius:5px;">
          <h4>2. User Data (JSONPlaceholder)</h4>
          <p>Name: ${user.name} | Email: ${user.email}</p>
        </div>
        <div style="background:#eef7ee; padding:10px; border-radius:5px;">
          <h4>3. Todo Item (JSONPlaceholder)</h4>
          <p>Task: ${todo.title} | Completed: ${todo.completed ? '✅' : '❌'}</p>
        </div>
      </div>
    `;

  } catch (error) {
    showError(multiResult, 'One or more requests failed.');
    console.error(error);
  }
}

if (btnFetchAll) btnFetchAll.addEventListener('click', fetchAllParallel);