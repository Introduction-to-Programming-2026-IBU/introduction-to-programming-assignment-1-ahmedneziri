/**
 * Exercise 5: Forms & Validation
 * ================================
 * Add real-time validation and submit handling.
 * Read README.md for full instructions.
 */

const form = document.querySelector('#registration-form');

// ============================================================
// HELPER: Show or clear an error on a field
// ============================================================
function showError(inputId, message) {
  // TODO: Add class 'invalid' to the input element
  const input = document.getElementById(inputId);
  if (input) {
    input.classList.remove('valid');
    input.classList.add('invalid');
  }
  // TODO: Set the text of the corresponding error-msg span to `message`
  const errorSpan = document.getElementById(`error-${inputId}`);
  if (errorSpan) {
    errorSpan.textContent = message;
  }
}

function clearError(inputId) {
  // TODO: Remove class 'invalid', add class 'valid' to the input
  const input = document.getElementById(inputId);
  if (input) {
    input.classList.remove('invalid');
    input.classList.add('valid');
  }
  // TODO: Clear the error-msg span text
  const errorSpan = document.getElementById(`error-${inputId}`);
  if (errorSpan) {
    errorSpan.textContent = '';
  }
}


// ============================================================
// TASK 2: Individual Field Validators
// (Return true if valid, false if invalid)
// ============================================================

function validateName() {
  // TODO: Get #full-name value
  const nameInput = document.getElementById('full-name');
  if (!nameInput) return false;
  const value = nameInput.value.trim();
  
  // If < 2 chars: showError, return false
  if (value.length < 2) {
    showError('full-name', 'Name must be at least 2 characters long.');
    return false;
  } 
  // Else: clearError, return true
  else {
    clearError('full-name');
    return true;
  }
}

function validateEmail() {
  // TODO: Get #email value
  const emailInput = document.getElementById('email');
  if (!emailInput) return false;
  const value = emailInput.value.trim();
  
  // Use regex /^[^\s@]+@[^\s@]+\.[^\s@]+$/ to test
  const emailRegex = /^[^\s@]+@[^\s@]+\.[^\s@]+$/;
  
  // showError or clearError appropriately
  if (!emailRegex.test(value)) {
    showError('email', 'Please enter a valid email address.');
    return false;
  } else {
    clearError('email');
    return true;
  }
}

function validatePassword() {
  // TODO: Get #password value
  const passwordInput = document.getElementById('password');
  if (!passwordInput) return false;
  const value = passwordInput.value;
  
  // Update #password-strength indicator (Task 4)
  updatePasswordStrength(value);

  // Must be 8+ chars AND contain at least one digit
  if (value.length < 8 || !/\d/.test(value)) {
    showError('password', 'Password must be at least 8 characters and contain a number.');
    return false;
  } else {
    clearError('password');
    return true;
  }
}

function validateConfirmPassword() {
  // TODO: Get #password and #confirm-password values
  const passwordInput = document.getElementById('password');
  const confirmInput = document.getElementById('confirm-password');
  if (!passwordInput || !confirmInput) return false;
  
  // They must match
  if (confirmInput.value === '') {
    showError('confirm-password', 'Please confirm your password.');
    return false;
  } else if (passwordInput.value !== confirmInput.value) {
    showError('confirm-password', 'Passwords do not match.');
    return false;
  } else {
    clearError('confirm-password');
    return true;
  }
}

function validateAge() {
  // TODO: Get #age value (convert to Number)
  const ageInput = document.getElementById('age');
  if (!ageInput) return true; // Optional fail-safe if age field isn't in HTML
  
  const value = ageInput.value.trim();
  const ageNum = Number(value);
  
  // Must be 18–120
  if (value === '' || isNaN(ageNum) || ageNum < 18 || ageNum > 120) {
    showError('age', 'Age must be a number between 18 and 120.');
    return false;
  } else {
    clearError('age');
    return true;
  }
}

function validateCountry() {
  // TODO: Get #country value
  const countryInput = document.getElementById('country');
  if (!countryInput) return false;
  
  // Must not be the default empty option
  if (countryInput.value === '') {
    showError('country', 'Please select your country.');
    return false;
  } else {
    clearError('country');
    return true;
  }
}

function validateTerms() {
  // TODO: Get #terms checkbox
  const termsCheckbox = document.getElementById('terms');
  if (!termsCheckbox) return false;
  
  // Must be checked
  if (!termsCheckbox.checked) {
    showError('terms', 'You must agree to the Terms and Conditions.');
    return false;
  } else {
    clearError('terms');
    return true;
  }
}


// ============================================================
// TASK 4: Password Strength Indicator
// ============================================================
function updatePasswordStrength(password) {
  // TODO: Get #password-strength element
  const strengthIndicator = document.getElementById('password-strength');
  if (!strengthIndicator) return;
  
  // Determine strength: weak / fair / strong
  // Update element's class and text
  strengthIndicator.classList.remove('weak', 'fair', 'strong');
  
  if (password.length === 0) {
    strengthIndicator.textContent = '';
  } else if (password.length < 8 || !/\d/.test(password)) {
    strengthIndicator.textContent = 'Weak';
    strengthIndicator.classList.add('weak');
  } else if (password.length >= 8 && /\d/.test(password) && /[A-Z]/.test(password) && /[!@#$%^&*]/.test(password)) {
    strengthIndicator.textContent = 'Strong';
    strengthIndicator.classList.add('strong');
  } else {
    strengthIndicator.textContent = 'Fair';
    strengthIndicator.classList.add('fair');
  }
}


// ============================================================
// TASK 5: Bio Character Counter
// ============================================================
const bioTextarea = document.querySelector('#bio');
// TODO: Add 'input' event listener to bioTextarea
if (bioTextarea) {
  bioTextarea.addEventListener('input', () => {
    const charCount = document.getElementById('char-count');
    const submitBtn = document.getElementById('submit-btn');
    const length = bioTextarea.value.length;
    
    // Update #char-count text: "X / 200 characters"
    if (charCount) {
      charCount.textContent = `${length} / 200 characters`;
      
      // If over 200: add 'over-limit' class, disable submit button
      if (length > 200) {
        charCount.classList.add('over-limit');
        if (submitBtn) submitBtn.disabled = true;
      } else {
        charCount.classList.remove('over-limit');
        if (submitBtn) submitBtn.disabled = false;
      }
    }
  });
}


// ============================================================
// TASK 2: Attach real-time listeners
// ============================================================
// TODO: Add 'blur' (or 'input') event listeners to each field
// that call its validator function
document.getElementById('full-name')?.addEventListener('blur', validateName);
document.getElementById('email')?.addEventListener('blur', validateEmail);
document.getElementById('password')?.addEventListener('input', validatePassword);
document.getElementById('confirm-password')?.addEventListener('blur', validateConfirmPassword);
document.getElementById('age')?.addEventListener('blur', validateAge);
document.getElementById('country')?.addEventListener('change', validateCountry);
document.getElementById('terms')?.addEventListener('change', validateTerms);


// ============================================================
// TASK 3: Submit Handler
// ============================================================
form.addEventListener('submit', function(event) {
  event.preventDefault(); // Always prevent default first

  // TODO: Run all validators and collect results
  // const results = [validateName(), validateEmail(), ...]
  const results = [
    validateName(),
    validateEmail(),
    validatePassword(),
    validateConfirmPassword(),
    validateAge(),
    validateCountry(),
    validateTerms()
  ];

  const allValid = results.every(result => result === true);

  // TODO: If all true → show #success-message, hide form
  if (allValid) {
    const successMsg = document.getElementById('success-message');
    if (successMsg) successMsg.classList.remove('hidden');
    form.style.display = 'none';
  } 
  // TODO: If any false → scroll to first invalid field
  else {
    const firstInvalidField = document.querySelector('.invalid');
    if (firstInvalidField) {
      firstInvalidField.scrollIntoView({ behavior: 'smooth', block: 'center' });
      firstInvalidField.focus();
    }
  }
});