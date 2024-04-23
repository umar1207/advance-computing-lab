// app.js
const express = require('express');
const bodyParser = require('body-parser');
const { generateTableHTML } = require('./utils/generate_table');
const fs = require('fs');

const app = express();
const PORT = process.env.PORT || 3000;

app.use(bodyParser.urlencoded({ extended: false }));
app.use(express.static('public'));
const { getAllStudents, searchStudent, insertStudent, deleteStudent } = require('./database/queries');

app.get('/', (req, res) => {
    // Read the contents of index.html
    fs.readFile(__dirname + '/views/index.html', 'utf8', (err, indexHTML) => {
        if (err) {
            console.error('Error reading index.html: ', err);
            res.status(500).send('Internal Server Error');
            return;
        }

        // Retrieve the database content
        getAllStudents((err, students) => {
            if (err) {
                console.error('Error retrieving students: ', err);
                res.status(500).send('Internal Server Error');
                return;
            }
            const userdetails = generateTableHTML(students);

            // Combine index.html content with database content
            const combinedHTML = indexHTML.replace('<!-- userdetailsplaceholder  -->', userdetails);
            res.send(combinedHTML);
        });
    });
});


// Search route
app.get('/search', (req, res) => {
    res.sendFile(__dirname + '/views/search.html');
});

app.post('/search', (req, res) => {
    // Process the search request
    const student = req.body;
    searchStudent(student, (err, result) => {
        if (err) {
            console.error('Error in retrieving students: ', err);
            res.status(500).send('Internal Server Error');
            return;
        }
        const searchResultsHTML = generateTableHTML(result);

        // Read the search form HTML
        fs.readFile(__dirname + '/views/search.html', 'utf8', (err, formData) => {
            if (err) {
                console.error('Error reading search form HTML: ', err);
                res.status(500).send('Internal Server Error');
                return;
            }

            // Combine the search form and search results HTML
            const combinedHTML = formData.replace('<!-- searchResultsPlaceholder -->', searchResultsHTML);
            res.send(combinedHTML);
        });
    });
});


// Insert route
app.get('/insert', (req, res) => {
    res.sendFile(__dirname + '/views/insert.html');
});

app.post('/insert', (req, res) => {
    const student = req.body;
    insertStudent(student, (err, result) => {
        if (err) {
            res.send('<script>alert("Student is already registered!"); window.history.back();</script>');
            return;
        }
        res.redirect('/');
    });
});

// Delete route

app.post('/delete', (req, res) => {
    const enrollmentNumber = req.body.enrollmentNumber;
    deleteStudent(enrollmentNumber, (err, result) => {
        if (err) {
            console.error('Error deleting student:', err);
            res.status(500).send('Internal Server Error');
            return;
        }
        res.redirect('/');
    });
});

// Start server
app.listen(PORT, () => {
    console.log(`Server is running on port http://127.0.0.1:${PORT}`);
});
