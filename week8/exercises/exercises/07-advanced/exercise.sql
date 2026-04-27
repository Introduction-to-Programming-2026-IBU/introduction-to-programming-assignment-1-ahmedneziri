-- Exercise 07: Advanced SQL
-- Databases: school.db and library.db

.headers on
.mode column

-- 7.1: Create an index on students.gpa, then EXPLAIN QUERY PLAN
CREATE INDEX idx_students_gpa ON students(gpa);
EXPLAIN QUERY PLAN SELECT * FROM students WHERE gpa > 3.5;

-- 7.2: Create view 'enrollment_details', then query for 'A' grades
CREATE VIEW enrollment_details AS
SELECT s.first_name, s.last_name, c.title, g.letter_grade
FROM enrollments e
JOIN students s ON e.student_id = s.id
JOIN courses c ON e.course_id = c.id
JOIN grades g ON e.id = g.enrollment_id;

SELECT * FROM enrollment_details WHERE letter_grade = 'A';

-- 7.3: Create view 'course_statistics' with count and avg final score
CREATE VIEW course_statistics AS
SELECT c.title, COUNT(e.student_id) AS student_count, ROUND(AVG(g.final), 1) AS avg_final_score
FROM courses c
LEFT JOIN enrollments e ON c.id = e.course_id
LEFT JOIN grades g ON e.id = g.enrollment_id
GROUP BY c.id;

-- 7.4: Insert a new student (newstudent@school.edu, 2024, NULL gpa)
INSERT INTO students (first_name, last_name, email, enrollment_year, gpa) 
VALUES ('New', 'Student', 'newstudent@school.edu', 2024, NULL);

-- 7.5: Update student id=17 (Quinn Moore) to set gpa = 3.22
UPDATE students SET gpa = 3.22 WHERE id = 17;

-- 7.6: Preview and then DELETE all grades with letter_grade = 'F'
-- Step 1: SELECT to preview (run this first!)
SELECT * FROM grades WHERE letter_grade = 'F';

-- Step 2: DELETE (uncomment when ready)
DELETE FROM grades WHERE letter_grade = 'F';

-- 7.7: Transaction to enroll student 1 in course 13 + add grade record
BEGIN TRANSACTION;
INSERT INTO enrollments (student_id, course_id, enrollment_date) 
VALUES (1, 13, DATE('now'));
INSERT INTO grades (enrollment_id) 
VALUES (last_insert_rowid());
COMMIT;

-- 7.8: Transaction: decrease available_copies for book 3, insert loan (library.db)
-- Assuming 'books' has an 'available_copies' column and 'loans' links members to books.
BEGIN TRANSACTION;
UPDATE books SET available_copies = available_copies - 1 WHERE id = 3;
INSERT INTO loans (member_id, book_id, loan_date) VALUES (1, 3, DATE('now'));
COMMIT;

-- 7.9: EXPLAIN QUERY PLAN comparison
-- Run both and compare the output:

-- Version A (may not use index well):
EXPLAIN QUERY PLAN SELECT * FROM students WHERE gpa + 0 > 3.5;

-- Version B (index-friendly):
EXPLAIN QUERY PLAN SELECT * FROM students WHERE gpa > 3.5;

-- Your explanation of the difference (as a comment):
-- Version A modifies the column with an expression ("+ 0") before comparing it. 
-- This forces the database engine to perform a full table scan, calculating the expression for every row.
-- Version B compares the raw column directly, allowing the database to utilize the B-tree index created in 7.1 to efficiently locate the matching records without scanning the entire table.

-- 7.10 CHALLENGE: Create compound index for enrollments(student_id, course_id)
CREATE UNIQUE INDEX idx_enrollments_student_course ON enrollments(student_id, course_id);