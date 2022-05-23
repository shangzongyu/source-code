# patients.sql

DROP TABLE IF EXISTS patients;
#@_CREATE_TABLE_
CREATE TABLE `patients` (
  `id` int NOT NULL AUTO_INCREMENT,
  `national_id` char(32) DEFAULT NULL,
  `name` varchar(255) DEFAULT NULL,
  `surname` varchar(255) DEFAULT NULL,
  `gender` enum('F','M') DEFAULT NULL,
  `age` tinyint unsigned DEFAULT NULL,
  `additional_data` json DEFAULT NULL,
  `diagnosis` varchar(255) DEFAULT NULL,
  `result` enum('R', 'N', 'D') DEFAULT NULL comment 'R=Recovered, N=Not Recovered, D=Dead',
  `date_arrived` date NOT NULL,
  `date_departed` date DEFAULT NULL,
  PRIMARY KEY (`id`)
);
#@_CREATE_TABLE_

INSERT INTO patients (national_id, name, surname, gender, age, diagnosis, result, date_arrived, date_departed)
  VALUES
    ('89AR642465', 'Mary', 'Smith', 'F', 24, 'Appendicitis', 'R', '2020-01-15', '2020-01-20'),
    ('71GE601633', 'John', 'Johnson', 'M', 57, 'Asthma', 'N', '2020-03-10', '2020-03-25'),
    ('15QT023022', 'Margaret', 'Williams', 'F', 50, 'Breast Cancer', 'D', '2020-05-08', '2020-08-07'),
    ('84DC051879', 'William', 'Brown', 'M', 64, 'Arthritis', 'N', '2020-05-10', '2020-05-27'),
    ('54XT916306', 'Elizabeth', 'Jones', 'F', 39, 'Data Phobia', 'R', '2020-04-17', '2020-06-03'),
    ('06VZ647400', 'James', 'Garcia', 'M', 86, 'Diabetes', 'D', '2020-08-09', '2020-08-15'),
    ('02WS884704', 'Sarah', 'Miller', 'F', 31, 'Diabetes', 'R', '2020-08-10', '2020-08-20'),
    ('78FS043029', 'David', 'Davis', 'M', 75, 'Arthritis', 'N', '2020-06-13', '2020-06-22'),
    ('45MY529190', 'Patricia', 'Rodriguez', 'F', 35, 'Diabetes', 'N', '2020-02-18', '2020-03-02'),
    ('30NC108735', 'Robert', 'Martinez', 'M', 35, 'Appendicitis', 'R', '2020-09-12', '2020-09-18'),
    ('38BP394037', 'Catherine', 'Hernandez', 'F', 61, 'Asthma', 'R', '2020-07-13', '2020-07-19'),
    ('96HE717336', 'Michael', 'Lopez', 'M', 33, 'Data Phobia', 'D', '2020-09-15', '2020-09-20'),
    ('26ES505212', 'Susan', 'Gonzalez', 'F', 81, 'Data Phobia', 'R', '2020-10-01', '2020-10-28'),
    ('04WT954962', 'Peter', 'Wilson', 'M', 86, 'Diabetes', 'N', '2020-09-26', '2020-10-07'),
    ('65XJ029932', 'Helen', 'Anderson', 'F', 57, 'Data Phobia', 'R', '2020-10-06', '2020-10-26'),
    ('59DW008178', 'Thomas', 'Thomas', 'M', 53, 'Data Phobia', 'R', '2020-09-15', '2020-10-26'),
    ('99XC682639', 'Emma', 'Taylor', 'F', 69, 'Breast Cancer', 'R', '2020-07-18', '2020-09-15'),
    ('72TY932806', 'George', 'Moore', 'M', 20, 'Data Phobia', 'R', '2020-11-01', '2020-11-10'),
    ('28VU492728', 'Alice', 'Jackson', 'F', 72, 'Arthritis', 'N', '2020-10-01', '2020-11-10'),
    ('09SK434607', 'Richard', 'Martin', 'M', 23, 'Asthma', 'N', '2020-11-18', '2020-11-28')
;

SELECT * FROM patients;
