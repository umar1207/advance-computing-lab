// database/queries.js
const db = require('./pool');

function getAllStudents(callback) {
    const query = 'SELECT * FROM students';
    db.query(query, (err, results) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, results);
    });
}

function insertStudent(student, callback) {
    const query = 'INSERT INTO students SET ?';
    db.query(query, student, (err, result) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, result);
    });
}

function deleteStudent(enrollmentNumber, callback) {
    const query = 'DELETE FROM students WHERE enrollmentNumber = ?';
    db.query(query, enrollmentNumber, (err, result) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, result);
    });
}

function searchStudent(student, callback) {
    let query = 'SELECT * FROM students WHERE 1=1'; // Start with a true condition
    if (student.name) query += ` AND name = '${student.name}'`;
    if (student.enrollmentNumber) query += ` AND enrollmentNumber = '${student.enrollmentNumber}'`;
    if (student.facultyNumber) query += ` AND facultyNumber = '${student.facultyNumber}'`;
    if (student.branch) query += ` AND branch = '${student.branch}'`;
    if (student.course) query += ` AND course = '${student.course}'`;
    if (student.semester) query += ` AND semester = '${student.semester}'`;
    if (student.hostelAllotted) query += ` AND hostelAllotted = '${student.hostelAllotted}'`;
    if (student.address) query += ` AND address = '${student.address}'`;

    db.query(query, (err, result) => {
        if (err) {
            callback(err, null);
            return;
        }
        callback(null, result);
    });
}
module.exports = { getAllStudents, insertStudent, searchStudent, deleteStudent };
