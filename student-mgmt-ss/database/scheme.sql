CREATE DATABASE IF NOT EXISTS student_db;

USE student_db;

CREATE TABLE IF NOT EXISTS students (
    name VARCHAR(255) NOT NULL,
    enrollmentNumber VARCHAR(20) NOT NULL UNIQUE,
    facultyNumber VARCHAR(20) NOT NULL UNIQUE,
    course VARCHAR(50) NOT NULL,
    branch VARCHAR(50) NOT NULL,
    semester VARCHAR(8) NOT NULL,
    hostelAllotted VARCHAR(50) NOT NULL,
    address VARCHAR(255) NOT NULL,
    PRIMARY KEY (enrollmentNumber)
);
