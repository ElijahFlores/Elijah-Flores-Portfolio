// Import the 'fs' module for interacting with the file system
const fs = require("fs");
const Sequelize = require('sequelize');

//DB Credentials

const { Pool } = require('pg');
const pool = new Pool({
  user:'neondb_owner',
  host:'ep-blue-dust-a5zf2e48.us-east-2.aws.neon.tech',
  database:'neondb',
  password:'Cmd9oENb8QXF',
  port: 5432,
  ssl: { rejectUnauthorized: false }
});


// Arrays to store categories and articles data loaded from JSON files
let categories = [];
let articles = [];

// Function to initialize data by loading categories and articles from JSON files
function initialize() {
  return new Promise((resolve, reject) => {
    // Read the categories data from categories.json file
    console.log("Run Initialize Function");
    fs.readFile("./data/categories.json", "utf8", (err, cat) => {
      if (err) return reject(err); // Reject the promise if an error occurs during file read
      categories = JSON.parse(cat); // Parse and store categories data

      // Nested readFile for articles.json
      // We nest the second file read inside the first because we want to ensure that categories.json
      // is successfully read and parsed before moving on to articles.json.
      // This way, we load both files sequentially and can handle any errors independently.
      fs.readFile("./data/articles.json", "utf8", (err, art) => {
        if (err) return reject(err); // Reject the promise if an error occurs during file read
        articles = JSON.parse(art); // Parse and store articles data
        articles.forEach(function(obj) {obj.categoryName = getNameByCategoryID(obj.category)}); //Get Category Name based on ID
        
        // We call resolve() only once, after both files have been successfully read and parsed.
        // Calling resolve() here signifies that initialization is complete and both categories
        // and articles data are ready for use. If we called resolve() earlier, it would 
        // prematurely indicate that initialization was complete before loading both files.
        resolve(); 
      });
    });
  });
}

// Function to get only published articles by filtering the articles array
function getPublishedArticles() {
  console.log("Run getPublishedArticles Function");
  return pool.query('SELECT articles.id, title, content, author, published, category, articledate, featureimage, name FROM articles JOIN categories ON categories.id = articles.category WHERE published IS TRUE')
    .then(res => res.rows)
    .catch(err => Promise.reject('No results returned'));
}

// Function to get all categories
function getCategories() {
  console.log("Run getCategories Function");
  return pool.query('SELECT * FROM categories')
  .then(res => res.rows)
  .catch(err => Promise.reject('No results returned'));
}

// Function to get all articles
function getArticles() {
  console.log("Run getArticles Function");
  return pool.query('SELECT articles.id, title, content, author, published, category, articledate, featureimage, name FROM articles JOIN categories ON categories.id = articles.category')
    .then(res => res.rows)
    .catch(err => Promise.reject('No results returned'));
};

// Function to add article
function addArticle(articleData) {
    console.log("Run addArticle Function");
    return new Promise((resolve, reject) => {
        articleData.published = articleData.published ? true : false;
        articleData.id = articles.length + 1; // Set ID to the current length + 1
        articles.push(articleData);
        resolve(articleData);
    });
}

// Function to get an article by category
function getArticlesByCategory(category){
    console.log("Run getArticlesByCategory Function");
    return pool.query('SELECT articles.id, title, content, author, published, category, articledate, featureimage, name FROM articles JOIN categories ON categories.id = articles.category WHERE category =' + category)
    .then(res => res.rows)
    .catch(err => Promise.reject('No results returned'));
}

// Function to get an article by Date
function getArticlesByMinDate(minDateStr){
    console.log("Run getArticlesByMinDate Function");
    return new Promise((resolve, reject) => {
        const minDate = new Date(minDateStr);
        const filteredArticles = articles.filter(article => newDate(article.articleDate) >= minDate);
        if (filteredArticles.length > 0){
            resolve(filteredArticles);
        } else {
            reject("no results returned");
        }
    });
}

// Function to get an article by ID
function getArticleByID(id){
    console.log("Run getArticleByID Function");
    return pool.query('SELECT articles.id, title, content, author, published, category, articledate, featureimage, name FROM articles JOIN categories ON categories.id = articles.category WHERE articles.id =' + id)
    .then(res => res.rows)
    .catch(err => Promise.reject('No results returned'));
}

// Function to get the category name by ID
function getNameByCategoryID(id){
    console.log("Run getNameByCategoryID Function");
    const selectedCategory = categories.find(category => category.Id == id);
    const selectedName = selectedCategory.Name;

    return selectedName;
}

// Export the functions as an object to make them available to other files
module.exports = { 
    initialize, 
    getCategories, 
    getArticles,
    addArticle,
    getArticlesByCategory,
    getArticlesByMinDate,
    getArticleByID,
    getNameByCategoryID
};
