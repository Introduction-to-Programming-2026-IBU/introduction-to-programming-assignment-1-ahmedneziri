-- Exercise 05: Subqueries
-- Databases: school.db and library.db

.headers on
.mode column

-- 5.1: Students with GPA above the average (school.db)
SELECT first_name, last_name, gpa 
FROM students 
WHERE gpa > (SELECT AVG(gpa) FROM students);

-- 5.2: Students enrolled in CS50 (use subquery) (school.db)
SELECT first_name, last_name 
FROM students 
WHERE id IN (
    SELECT student_id 
    FROM enrollments 
    WHERE course_id = (SELECT id FROM courses WHERE code = 'CS50')
);

-- 5.3: Students NOT enrolled in CS50 (school.db)
SELECT first_name, last_name 
FROM students 
WHERE id NOT IN (
    SELECT student_id 
    FROM enrollments 
    WHERE course_id = (SELECT id FROM courses WHERE code = 'CS50')
);

-- 5.4: Courses taught by the highest-paid teacher (school.db)
SELECT title 
FROM courses 
WHERE teacher_id = (
    SELECT id 
    FROM teachers 
    WHERE salary = (SELECT MAX(salary) FROM teachers)
);

-- 5.5: Students enrolled in 3 or more courses (subquery in FROM) (school.db)
SELECT s.first_name, s.last_name, ec.course_count
FROM students s
JOIN (
    SELECT student_id, COUNT(course_id) AS course_count
    FROM enrollments
    GROUP BY student_id
    HAVING COUNT(course_id) >= 3
) ec ON s.id = ec.student_id;

-- 5.6: Members who borrowed more than 2 books (library.db)
SELECT m.first_name, m.last_name
FROM members m
JOIN (
    SELECT member_id, COUNT(book_id) AS book_count
    FROM loans
    GROUP BY member_id
    HAVING COUNT(book_id) > 2
) lc ON m.id = lc.member_id;

-- 5.7: Books with more pages than average (library.db)
SELECT title, pages 
FROM books 
WHERE pages > (SELECT AVG(pages) FROM books);

-- 5.8: Students with at least one grade (EXISTS) (school.db)
SELECT first_name, last_name 
FROM students s
WHERE EXISTS (
    SELECT 1 
    FROM enrollments e
    JOIN grades g ON e.id = g.enrollment_id
    WHERE e.student_id = s.id AND g.letter_grade IS NOT NULL
);

-- 5.9: Courses with no grades recorded (NOT EXISTS) (school.db)
SELECT title 
FROM courses c
WHERE NOT EXISTS (
    SELECT 1 
    FROM enrollments e
    JOIN grades g ON e.id = g.enrollment_id
    WHERE e.course_id = c.id AND g.letter_grade IS NOT NULL
);

-- 5.10 CHALLENGE: Course(s) with the most enrollments (no LIMIT) (school.db)
SELECT c.title, COUNT(e.student_id) AS total_enrollments
FROM courses c
JOIN enrollments e ON c.id = e.course_id
GROUP BY c.id
HAVING COUNT(e.student_id) = (
    SELECT MAX(enrollment_count) 
    FROM (
        SELECT COUNT(student_id) AS enrollment_count
        FROM enrollments
        GROUP BY course_id
    )
);