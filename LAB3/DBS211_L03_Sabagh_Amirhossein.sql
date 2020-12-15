-- Amirhossein Sabagh | 152956199 | 2020/06/05 | DBS211 - Lab03

SET AUTOCOMMIT ON;

-- 1.
SELECT * 
    FROM offices;  

--2.
SELECT employeenumber 
    FROM employees
        WHERE officecode = 1;

--3.
SELECT customernumber, customername,
contactfirstname, contactlastname, phone
    FROM customers
        WHERE city = 'Paris';
        
--4.
SELECT customernumber, customername, 
contactfirstname || ' ' || contactlastname 
AS "lastname, firstname", phone
    FROM customers
        WHERE country = 'Canada';

--5.
SELECT DISTINCT customernumber 
    FROM payments;
    
--6.
SELECT customernumber, checknumber, amount
    FROM payments
        WHERE amount NOT BETWEEN 30000 and 65000
            ORDER BY amount DESC;

--7.
SELECT * 
    FROM orders 
        WHERE status = 'Cancelled';

--8.
SELECT productcode, productname, buyprice, msrp,
msrp - buyprice AS markup, 
round((msrp - buyprice) / buyprice * 100,1) AS percmarkup
    FROM products;

--9.
SELECT *
    FROM products
        WHERE LOWER(productname) LIKE '%co%';

--10.
SELECT *
    FROM customers
        WHERE LOWER(contactfirstname) LIKE 's%' 
        AND LOWER(contactfirstname) LIKE '%e%';

--11.
INSERT INTO employees
VALUES (1666, 'Sabagh', 'Amir', 'x666', 'asabagh@myseneca.ca', 4, 1088, 'Cashier');

--.12
SELECT *
    FROM employees
        WHERE employeenumber = 1666;
        
--13.        
UPDATE employees
    SET jobtitle = 'Head Cashier'
        WHERE employeenumber = 1666;
        
--14.
INSERT INTO employees
VALUES (1000, 'Flannel', 'Richard', 'x7070', 'richardisfictional@gmail.com', 4, 1666, 'Cashier');

--15.
DELETE FROM employees
    WHERE employeenumber = 1666;

--16.
DELETE FROM employees
    WHERE employeenumber = 1000;
    
--17.
-- if we just want to undo the last 2 statemnts : ROLLBACK 2
INSERT ALL 
INTO employees VALUES (1666, 'Sabagh', 'Amir', 'x666', 'asabagh@myseneca.ca', 4, 1088, 'Cashier')
INTO employees VALUES (1000, 'Flannel', 'Richard', 'x7070', 'richardisfictional@gmail.com', 4, 1088, 'Cashier')
SELECT * FROM dual;

--18.
DELETE FROM employees
    WHERE employeenumber = 1666;
    -- I checked the "CASCADE Drops" box in Utilities: Export pane