-- Cleanup.

ALTER TABLE Customers DROP CONSTRAINT
FK_CustomerOrder;

ALTER TABLE Customers DROP CONSTRAINT
FK_CustomerEmployee;

ALTER TABLE OrderProduct DROP CONSTRAINT
FK_OrderProduct_Order;

ALTER TABLE OrderProduct DROP CONSTRAINT
FK_OrderProduct_Product;

DROP TABLE Customers;
DROP TABLE Orders;
DROP TABLE Products;
DROP TABLE Employees;
DROP TABLE Menus;
DROP TABLE OrderProduct;


-- Create all the tables.

CREATE TABLE Customers
(
    CustomerId INTEGER NOT NULL,
    CustomerName VARCHAR(50) NOT NULL,
    Phone VARCHAR(50) NOT NULL,
    Address VARCHAR(50),
    
    OrderId INTEGER,
    EmployeeId INTEGER,
    CONSTRAINT customer_pk PRIMARY KEY(CustomerId)
);

CREATE TABLE Orders
(
    OrderId INTEGER NOT NULL,
    OrderDate VARCHAR(50) NOT NULL,
    CONSTRAINT order_pk PRIMARY KEY(OrderId)
);

CREATE TABLE Products
(
    ProductId INTEGER NOT NULL,
    ProductName VARCHAR(50) NOT NULL,
    Price DOUBLE PRECISION NOT NULL,
    Kcal INTEGER,
    CONSTRAINT product_pk PRIMARY KEY(ProductId)
);

CREATE TABLE Employees
(
    EmployeeId INTEGER NOT NULL,
    EmployeeName VARCHAR(50) NOT NULL,
    Salary INTEGER,
    CONSTRAINT employee_pk PRIMARY KEY(EmployeeId)
);

CREATE TABLE Menus
(
    MenuId INTEGER NOT NULL,
    MenuName VARCHAR(50) NOT NULL,
    Description VARCHAR(150) NOT NULL,
    Price DOUBLE PRECISION NOT NULL,
    CONSTRAINT menu_pk PRIMARY KEY(MenuId)
);

CREATE TABLE OrderProduct
(
  OrderId INTEGER NOT NULL,
  ProductId INTEGER NOT NULL,
  CONSTRAINT op_order_pk PRIMARY KEY(OrderId)
);


-- Add foreign keys constraints.

ALTER TABLE Customers
    ADD CONSTRAINT FK_CustomerOrder
    FOREIGN KEY (OrderId)
    REFERENCES Orders(OrderId)
;

ALTER TABLE Customers
    ADD CONSTRAINT FK_CustomerEmployee
    FOREIGN KEY (EmployeeId)
    REFERENCES Employees(EmployeeId)
;

ALTER TABLE OrderProduct
    ADD CONSTRAINT FK_OrderProduct_Order
    FOREIGN KEY (OrderId)
    REFERENCES Orders(OrderId)
;

ALTER TABLE OrderProduct
    ADD CONSTRAINT FK_OrderProduct_Product
    FOREIGN KEY (ProductId)
    REFERENCES Products(ProductId)
;


-- Insert initial data (manual).

INSERT INTO Customers VALUES (
    1,
    'Poieana Costinel',
    '0743496790',
    NULL,
    NULL,
    NULL
);

INSERT INTO Orders VALUES (
    1,
    '17/03/2017'
);

INSERT INTO Products VALUES (
    1,
    'Apa minerala',
    4.5,
    NULL
);

INSERT INTO Employees VALUES (
    1,
    'Poieana Cosmin',
    2000
);

INSERT INTO Menus VALUES (
    1,
    'Meniul zilei',
    'Ciorba vacuta, gratar pui cu legume la cuptor, budinca chia.',
    49.99
);

-- Insert automatically generated data.

SET serveroutput on;
DECLARE
  contor NUMBER := 1;
BEGIN
  WHILE (contor < 10000) LOOP
    contor := contor + 1;
    
    INSERT INTO Employees
    VALUES (
      contor,
      CASE
          WHEN get_random_number(0,9) = 0 THEN 'Stavarki Bianca'
          WHEN get_random_number(0,9) = 1 THEN 'Iulius Flavius'
          WHEN get_random_number(0,9) = 2 THEN 'Minea Cristian'
          WHEN get_random_number(0,9) = 3 THEN 'Whilhem Eusebiu'
          WHEN get_random_number(0,9) = 4 THEN 'Popa Andreea'
          WHEN get_random_number(0,9) = 5 THEN 'Cazacu Ana'
          WHEN get_random_number(0,9) = 6 THEN 'Tihaia Oriana'
          WHEN get_random_number(0,9) = 7 THEN 'Poieana Vasile'
          WHEN get_random_number(0,9) = 8 THEN 'Crihan Cristian'
          WHEN get_random_number(0,9) = 9 THEN 'Pavel Emanuel'
      ELSE 'Popa Andreea' END,
      get_random_number(2000, 4000)
    );
    
    INSERT INTO Menus
    VALUES (
      contor,
      CASE
          WHEN get_random_number(0,9) = 0 THEN 'Meniu Bianca'
          WHEN get_random_number(0,9) = 1 THEN 'Meniu Flaviu'
          WHEN get_random_number(0,9) = 2 THEN 'Meniu Cristian'
          WHEN get_random_number(0,9) = 3 THEN 'Meniu Eusebiu'
          WHEN get_random_number(0,9) = 4 THEN 'Meniu Andreea'
          WHEN get_random_number(0,9) = 5 THEN 'Meniu Ana'
          WHEN get_random_number(0,9) = 6 THEN 'Meniu Oriana'
          WHEN get_random_number(0,9) = 7 THEN 'Meniu Vasile'
          WHEN get_random_number(0,9) = 8 THEN 'Meniu Cristian'
          WHEN get_random_number(0,9) = 9 THEN 'Meniu Emanuel'
      ELSE 'Meniu Andreea' END,
      CASE
          WHEN get_random_number(0,9) = 0 THEN 'Ciorba de perisoare'
          WHEN get_random_number(0,9) = 1 THEN 'Gratar cu legume'
          WHEN get_random_number(0,9) = 2 THEN 'Pavlova cu ciocolata si fructe'
          WHEN get_random_number(0,9) = 3 THEN 'Tort diplomat cu fructe '
          WHEN get_random_number(0,9) = 4 THEN 'Salata de vinete'
          WHEN get_random_number(0,9) = 5 THEN 'Bruschete cu rosii si mozarella'
          WHEN get_random_number(0,9) = 6 THEN 'Pui vanatoresc in sos alb'
          WHEN get_random_number(0,9) = 7 THEN 'Friptura de iepure in vin rosu'
          WHEN get_random_number(0,9) = 8 THEN 'Salata fructe de mare'
          WHEN get_random_number(0,9) = 9 THEN 'Sarmale cu mamaliguta'
      ELSE 'Tochitura in stil taranesc' END,
      DBMS_RANDOM.VALUE(15, 65)
    );
    
  END LOOP;
END;