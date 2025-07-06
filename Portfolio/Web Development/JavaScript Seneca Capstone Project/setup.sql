CREATE TABLE IF NOT EXISTS categories (
    Id            REAL      NOT NULL,
    Name         VARCHAR(50)    NOT NULL
);
INSERT INTO categories VALUES (1, 
'Artificial Intelligence');
INSERT INTO categories VALUES (2, 
'Machine Learning');
INSERT INTO categories VALUES (3, 
'Cybersecurity');
INSERT INTO categories VALUES (4, 
'Blockchain');
INSERT INTO categories VALUES (5, 
'Cloud Computing');
INSERT INTO categories VALUES (6, 
'Data Science');
INSERT INTO categories VALUES (7, 
'Internet of Things');
INSERT INTO categories VALUES (8, 
'Augmented Reality');
INSERT INTO categories VALUES (9, 
'Virtual Reality');
INSERT INTO categories VALUES (10, 
'Big Data');
INSERT INTO categories VALUES (11, 
'Quantum Computing');
INSERT INTO categories VALUES (12, 
'Mobile Development');
INSERT INTO categories VALUES (13, 
'Web Development');
INSERT INTO categories VALUES (14, 
'DevOps');
INSERT INTO categories VALUES (15, 
'E-commerce');
INSERT INTO categories VALUES (16, 
'Digital Marketing');
INSERT INTO categories VALUES (17, 
'3D Printing');
INSERT INTO categories VALUES (18, 
'Robotics');
INSERT INTO categories VALUES (19, 
'Game Development');
INSERT INTO categories VALUES (20, 
'Wearable Technology');

CREATE TABLE IF NOT EXISTS articles (
    Id            REAL      NOT NULL,
    title         VARCHAR(100)    NOT NULL,
    content       VARCHAR(1000)    NOT NULL,
    author        VARCHAR(30)     NOT NULL,
    published     BOOLEAN,
    category      REAL       NOT NULL,
    articleDate   VARCHAR(20),
    featureImage  VARCHAR(100)    NOT NULL
);

INSERT INTO articles VALUES (1, 
'The Rise of Artificial Intelligence', 
'Artificial Intelligence (AI) has become a transformative force in various industries, revolutionizing how we interact with technology. From automating mundane tasks to providing predictive insights, AI is changing the business landscape. This article explores the growing influence of AI and its potential impact on future job markets.',
'Alice Johnson',
true,
1,
'2024-01-15',
'https://dummyimage.com/600x400/000/fff');


INSERT INTO articles VALUES (2, 
'Machine Learning Techniques for Beginners', 
'Machine learning is a subset of AI that allows systems to learn and improve from experience without being explicitly programmed. This article breaks down beginner-friendly techniques such as linear regression and decision trees. It is an ideal starting point for anyone interested in the world of data-driven algorithms.',
'Bob Smith',
true,
2,
'2024-01-20',
'https://dummyimage.com/600x400/000/fff');


INSERT INTO articles VALUES (3, 
'Cybersecurity Tips for Small Businesses', 
'Cybersecurity is crucial for small businesses to protect against data breaches and cyber attacks. This guide covers essential tips, such as strong password policies, regular software updates, and employee training. Implementing these practices can significantly reduce the risk of cyber threats.',
'Carol White',
false,
3,
'2024-02-05',
'https://dummyimage.com/600x400/000/fff');


INSERT INTO articles VALUES (4, 
'Understanding Blockchain Technology', 
'Blockchain technology provides a decentralized way of recording transactions, making it more secure and transparent. In this article, we dive into the basics of blockchain, how it works, and potential applications beyond cryptocurrency. The technology holds promise for industries ranging from finance to healthcare.',
'Dave Lee',
true,
4,
'2024-02-10',
'https://dummyimage.com/600x400/000/fff');

INSERT INTO articles VALUES (5, 
'Cloud Computing Advantages', 
'Cloud computing offers flexible resources that can scale to meet a business changing needs. This article discusses the primary benefits of cloud adoption, including cost savings, enhanced collaboration, and improved data accessibility. As more companies embrace remote work, cloud solutions are becoming even more critical.',
'Emma King',
false,
5,
'2024-02-15',
'https://dummyimage.com/600x400/000/fff');
