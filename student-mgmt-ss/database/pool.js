const mysql = require('mysql');

// establish connection to the database
const connection = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: '21cob292-gm6617',
    database: 'student_db'
});

connection.connect((err) => {
    if (err) {
        console.error('Error connecting to database:', err);
        return;
    }
    console.log('Connected to database!');
});

module.exports = connection;