-- Amirhossein Sabagh | 152956199 | 2020/06/23 | DBS211 - Lab06


--1. List the 4 ways that we know that a transaction can be started:

    -- When You start a new session and type in the blank worksheet  
    -- BEGIN transaction
    -- COMMIT
    -- F11 (short key for commoit) 
    -- Any DDL statement like CREATE
    

--2. Using SQL, create an empty table, that is the same as the employees table, and name it newEmployees    
CREATE TABLE newEmployees AS
    SELECT *
        FROM employees;
TRUNCATE TABLE newEmployees;


--3. Execute the following commands
SET AUTOCOMMIT OFF; 
SET TRANSACTION READ WRITE;


--4. Write an INSERT statement to populate the newEmployees table with the rows of the sample data. 
-- Insert the NULL value for the reportsTo column. (Write a single INSERT statement to insert all the rows)
INSERT ALL
INTO newemployees VALUES (100, 'Patel', 'Ralph', 22333, 'rpatel@mail.com', 1, NULL, 'Sales Rep')
INTO newemployees VALUES (101, 'Denis', 'Betty', 33444, 'bdenis@mail.com', 4 , NULL ,'Sales Rep')
INTO newemployees VALUES (102, 'Biri', 'Ben', 44555, 'bbirir@mail.com', 2, NULL, 'Sales Rep')
INTO newemployees VALUES (103, 'Newman', 'Chad', 66777, 'cnewman@mail.com', 3, NULL, 'Sales Rep')
INTO newemployees VALUES (104, 'Ropeburn', 'Audrey', 77888, 'aropebur@mail.com', 1, NULL, 'Sales Rep')
SELECT * FROM dual;


--5. Create a query that shows all the inserted rows from the newEmployees table. 
SELECT * FROM newemployees;
-- How many rows are selected?      5 rows are selected



--6. Execute the rollback command. Display all rows and columns from the newEmployees table. 
ROLLBACK;
SELECT * FROM newemployees;
-- How many rows are selected?      0 rows are shown


--7. Repeat Task 4. Make the insertion permanent to the table newEmployees. 
-- Display all rows and columns from the newEmployee table. 
INSERT ALL
INTO newemployees VALUES (100, 'Patel', 'Ralph', 22333, 'rpatel@mail.com', 1, NULL, 'Sales Rep')
INTO newemployees VALUES (101, 'Denis', 'Betty', 33444, 'bdenis@mail.com', 4 , NULL ,'Sales Rep')
INTO newemployees VALUES (102, 'Biri', 'Ben', 44555, 'bbirir@mail.com', 2, NULL, 'Sales Rep')
INTO newemployees VALUES (103, 'Newman', 'Chad', 66777, 'cnewman@mail.com', 3, NULL, 'Sales Rep')
INTO newemployees VALUES (104, 'Ropeburn', 'Audrey', 77888, 'aropebur@mail.com', 1, NULL, 'Sales Rep')
SELECT * FROM dual;

COMMIT;
SELECT * FROM newemployees;
--How many rows are selected?       5 rows are selected



--8. Write an update statement to update the value of column jobTitle to ‘unknown’ 
-- for all the employees in the newEmployees table
UPDATE newemployees
SET jobtitle = 'unknown';


--9. Make your changes permanent
COMMIT;



--10. Execute the rollback command
ROLLBACK;

    -- a. Display all employees from the newEmployees table whose job title is ‘unknown’. 
SELECT * 
    FROM newemployees
        WHERE jobtitle = 'unknown';
        -- How many rows are still updated?         they are all updated
    
    --b. Was the rollback command effective?    NO
    
    --c. What was the difference between the result of the rollback execution from Task 6 and the result of the 
    --rollback execution of this task?          commit command in this task, force stopped the transaction and started another
    --one; therefore,the rollback command did literally nothing and undoed nothing. In task 6, we exectued rollback command 
    --while the transaction has not gotten stopped yet; so, it undoed all the statements before it.
    
    
    
--11. Begin a new transaction and then create a statement to delete to employees from the newEmployees table
COMMIT; -- or BEGIN...END;
    TRUNCATE TABLE newEmployees;
    
    
--12. Create a VIEW, called vwNewEmps, that queries all the records 
--    in the newEmployees table sorted by last name and then by first name.    
CREATE VIEW vwNewEmps AS
    SELECT *
        FROM newemployees
            ORDER BY lastname, firstname;
            
            
--13. Perform a rollback to undo the deletion of the employees
ROLLBACK;
    --a. How many employees are now in the newEmployees table?      0
    
    --b. Was the rollback effective and why?        It wasn't effective because by executing a DDL statement, techincally, 
    -- the transaction stops and a new transaction begins. The rollback command only undoes the view creation.
    

--14. Begin a new transaction and rerun the data insertion from Task 4 (copy the code down to Task 14 and run it)
COMMIT;
INSERT ALL
INTO newemployees VALUES (100, 'Patel', 'Ralph', 22333, 'rpatel@mail.com', 1, NULL, 'Sales Rep')
INTO newemployees VALUES (101, 'Denis', 'Betty', 33444, 'bdenis@mail.com', 4 , NULL ,'Sales Rep')
INTO newemployees VALUES (102, 'Biri', 'Ben', 44555, 'bbirir@mail.com', 2, NULL, 'Sales Rep')
INTO newemployees VALUES (103, 'Newman', 'Chad', 66777, 'cnewman@mail.com', 3, NULL, 'Sales Rep')
INTO newemployees VALUES (104, 'Ropeburn', 'Audrey', 77888, 'aropebur@mail.com', 1, NULL, 'Sales Rep')
SELECT * FROM dual;


--15.Set a Savepoint, called insertion, after inserting the data
SAVEPOINT insertion;


--16. Rerun the update statement from Task 8 and run a query to view the data (copy the code down and run it again)
UPDATE newemployees
SET jobtitle = 'unknown';
SELECT * FROM newemployees;


--17. Rollback the transaction to the Savepoint created in task 15 above and run a query to view the data.
--    What does the data look like (i.e. describe what happened?)
ROLLBACK TO insertion;
SELECT * FROM newemployees;
--      the rollback undoes the statements up until it reached the savepoint. So, it deleted the UPDATE satatement but 
--      the data itself was there intact.


--18. Use the basic for of the rollback statement and again view the data. 
--    Describe what the results look like and what happened.
ROLLBACK;
-- now the rollback undoes the actions and satatements of the whole transaction. Therefore, the data of the employees that we
-- inserted got deleted because it was in the transaction and rollback undoes it.
