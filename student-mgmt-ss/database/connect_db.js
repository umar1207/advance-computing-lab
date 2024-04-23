const mysql = require('mysql');
const fs = require('fs').promises;
const path = require('path');


async function initialise() {
    const connection = mysql.createConnection({
        host: 'localhost',
        user: 'root',
        password: '21cob292-gm6617'
    });

    try {
        await new Promise((resolve, reject) => {
            connection.connect((err) => {
                if (err) reject(err);
                else resolve();
            });
        });

        const schemaSQL = await fs.readFile(path.join(__dirname, 'scheme.sql'), 'utf8');
        const queries = schemaSQL.split(';').map(query => query.trim()).filter(Boolean);

        for (const query of queries) {
            await new Promise((resolve, reject) => {
                connection.query(query, (err, results) => {
                    if (err) reject(err);
                    else resolve();
                });
            });
        }

        console.log('Initialization complete!');
    } catch (error) {
        console.error('Initialization error:', error);
    }
    finally {
        connection.end();
    }
}

initialise();