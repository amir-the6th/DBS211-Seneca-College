-- Amirhossein Sabagh | 152956199 | 2020/06/13 | DBS211 - Lab04

SET AUTOCOMMIT ON;

-- 1.
    --ANSI-89 Join
SELECT employeenumber, firstname, lastname, city, phone, postalcode
    FROM employees, offices
        WHERE country = 'France';
    --ANSI-92 Join
SELECT employeenumber, firstname, lastname, city, phone, postalcode
    FROM employees
    INNER JOIN offices
    ON
    country = 'France';    

-- 2. 
SELECT customers.customernumber, customername, paymentdate AS "DATE(YY-MM-DD)", amount
    FROM customers
    INNER JOIN payments
    ON
    country = 'Canada'
    ORDER BY customers.customernumber;
    
-- 3.
SELECT customers.customernumber, customername  
    FROM customers
        WHERE customers.country = 'USA' AND customernumber 
        NOT IN(SELECT customernumber FROM payments);
    
    /* 
    SELECT customernumber
        FROM customers
        WHERE customers.country = 'USA'
        MINUS
    SELECT  customernumber
        FROM payments
        ORDER BY customernumber; 
    */
    

-- 4.
CREATE VIEW vwCustomerOrder AS
    SELECT orders.customernumber, orders.ordernumber, orders.orderdate, 
    products.productname, orderdetails.quantityordered, orderdetails.priceeach
    FROM ((orderdetails
    INNER JOIN products ON products.productcode = orderdetails.productcode)
    INNER JOIN orders ON orders.ordernumber = orderdetails.ordernumber);
SELECT * FROM vwcustomerorder;    
    

-- 5.
CREATE OR REPLACE VIEW vwCustomerOrder AS
    SELECT orders.customernumber, orders.ordernumber, orders.orderdate, products.productname, 
    orderdetails.quantityordered, orderdetails.priceeach, orderdetails.orderlinenumber
    FROM ((orderdetails
    INNER JOIN products ON products.productcode = orderdetails.productcode)
    INNER JOIN orders ON orders.ordernumber = orderdetails.ordernumber);
SELECT * FROM vwcustomerorder
    WHERE customernumber = 124
        ORDER BY ordernumber, orderlinenumber;


-- 6.     
SELECT customernumber, contactfirstname, contactlastname, phone, creditlimit   
    FROM customers
        WHERE customernumber NOT IN (SELECT customernumber FROM orders);    

-- 7.
CREATE VIEW vwEmployeeManager AS
    SELECT a.employeenumber, a.lastname, a.firstname, a.extension, a.email, 
    b.firstname || ' ' || b.lastname AS Reportsto, a.jobtitle
    FROM employees a 
    LEFT OUTER JOIN employees b
    ON a.reportsto = b.employeenumber
        ORDER BY a.employeenumber; -- I added this optionally for better look
SELECT * FROM vwemployeemanager;    


-- 8.
CREATE OR REPLACE VIEW vwEmployeeManager AS
    SELECT a.employeenumber, a.lastname, a.firstname, a.extension, a.email, 
        b.firstname || ' ' || b.lastname AS Reportsto, a.jobtitle
        FROM employees a 
        LEFT OUTER JOIN employees b
        ON (a.reportsto = b.employeenumber) AND (b.firstname || ' ' || b.lastname IS NOT NULL) --  != ' '
            ORDER BY a.employeenumber;  

-- 9.
DROP VIEW vwCustomerOrder;
DROP VIEW vwEmployeeManager;
