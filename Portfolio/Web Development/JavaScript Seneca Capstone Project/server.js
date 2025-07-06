// Import the Express library
const express = require("express");

// Import the 'path' module to handle file paths
const path = require("path");

// Set up the file upload for your web server.
const multer = require("multer"); 
const cloudinary = require('cloudinary').v2; 
const streamifier = require('streamifier'); 
// Import the custom data handling module, assumed to manage categories and articles
const contentData = require("./content-service");
// Create an Express application instance
const app = express();
// Set the HTTP port to an environment variable or default to 3838
const HTTP_PORT = process.env.PORT || 9999;
// No disk storage, files are stored in memory
const upload = multer();  
//Setup: Setup your server using Express.js and set EJS as your view engine.
app.set('view engine', 'ejs');
app.set('views', path.join(__dirname, 'views'));

// Cloudinary configuration
cloudinary.config({ 
    cloud_name: 'dzizkbkh1', 
    api_key: '336126829386296', 
    api_secret: 'N2He1dGPzvSxNZY68wpmoQvIoTA', 
    secure: true 
 }); 
// Serve static files from the "public" directory (e.g., CSS, JS files, images)
app.use(express.static("public"));


// Route for the root path, redirecting to the "/about" page
app.get("/", (req, res) => {
  res.redirect("/about");
});

// Route for the "/about" page, serving the "about.ejs" file
app.get("/about", (req, res) => {
  //res.sendFile(path.join(__dirname, "/views/about.ejs"));
  res.render('about');
});

// Route for the "/categories" endpoint, returning categories in JSON format
app.get("/categories", (req, res) => {
  contentData.getCategories()
  //.then((data) => {res.json(data)})// Respond with articles as JSON Removed in Assignment 4
  .then(data => res.render('categories', {categories: data})) // Assignment #4 change
  .catch((err) => {
    console.error("Error in /categories route", err);
    res.status(500).render('categories', {message: err});
});
});

// Route for the "/articles" endpoint, returning articles in JSON format
// Added Optional Filters for Assignment #3
app.get("/articles", (req, res) => {
    if(req.query.category){
        console.log("Running getArticlesByCategory function in server");
        contentData.getArticlesByCategory(req.query.category)
        //.then((data) => {res.json(data)})// Respond with articles as JSON Removed in Assignment 4
        .then(data => res.render('articles', {articles: data})) // Assignment #4 change
        .catch((err) => {
            console.error("Error in /articles route with category filter: ", err);
            res.status(500).render('articles', {message: err});
        });
    } else if (req.query.minDate) {
        console.log("Running getArticlesByMinDate function in server");
        contentData.getArticlesByMinDate(req.query.minDate)
        //.then((data) => {res.json(data)})// Respond with articles as JSON Removed in Assignment 4
        .then(data => res.render('articles', {articles: data})) // Assignment #4 change
        .catch((err) => {
            console.error("Error in /articles route with minDate filter: ", err);
            res.status(500).render('articles', {message: err});
        }); 
    } else {
        console.log("Running getArticles function in server");
        contentData.getArticles()
        //.then((data) => {res.json(data)})// Respond with articles as JSON Removed in Assignment 4
        .then(data => res.render('articles', {articles: data})) // Assignment #4 change
        .catch((err) => {
            console.error("Error in /articles route: ", err);
            res.status(500).render('articles', {message: err});
        }); 
    }
});

// Route to get an article by ID
app.get("/article/:Id", (req, res) => {
    contentData
      .getArticleByID(req.params.Id)
      .then((articles) => {
        const article = articles[0];
        if (article.published === true)
          res.render("article", { article: article });
        else res.status(404).json({ message: "404: Article Not Found" });
      })
      .catch((err) => {
        res.status(404).json({ message: err });
      });
  });

// Route for the "/articles/add" endpoint
app.get('/articles/add', (req, res) => { 
    //res.sendFile(path.join(__dirname, 'views', 'addArticle.ejs')); 
    res.render('addArticle');
 }); 

 // Route to handle adding a new article
app.post('/articles/add', upload.single("featureImage"), (req,res) =>{
    console.log('Received request to add an article: ', req.body);
    if (req.file){
        let streamUpload = (req) => {
            return new Promise((resolve, reject) => {
                let stream = cloudinary.uploader.upload_stream(
                    (error, result) => {
                        if (result) {
                            console.log('Upload Result: ', result);
                            resolve(result);
                        } else {
                            console.error('Upload error: ', error);
                            reject(error);
                        }
                    }
                );
                streamifier.createReadStream(req.file.buffer).pipe(stream);
            });
        };

        //Upload asynchronous function
        async function upload(req) {
            try {
                let result = await streamUpload(req);
                return result;
            } catch (error) {
                console.error('Upload error: ', error);
                throw error;
            }
        }

        //Upload Sequence
        upload(req).then((uploaded) => {
            console.log('Image uploaded: ', uploaded.url);
            processArticle(uploaded.url);
        }).catch(err => {
            console.error("Upload Error: ", err);
            res.status(500).json({message:"Image upload failed",error:err.message});
        });
    } else {
        processArticle("");
    }

    // Function to process the article
    function processArticle(imageURL){
        req.body.featureImage = imageURL;
        console.log('Processing image with URL: ', imageURL);

        // Add Article to content-service
        contentData.addArticle(req.body)
            .then(() => {
                console.log('Article add Success');
                res.redirect('/articles');
            })
            .catch(err => {
                console.error("Upload Error: ", err);
                res.status(500).json({message:"Article creation failed", error:err.message});
            })
    }
});

// Initialize the data in the contentData module, then start the server
contentData.initialize().then(() => {
  app.listen(HTTP_PORT); // Start server and listen on specified port
  console.log("server listening @ http://localhost:" + HTTP_PORT);
});

// Export the Express app instance (useful for testing or external usage)
module.exports = app;
