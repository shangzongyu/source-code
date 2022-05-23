#!/usr/bin/python3
# generate_patients_data.py: generate data in table patients

#First, import necessary packages
import numpy 
from pandas import pandas
import random 
import string
from datetime import datetime
from datetime import timedelta
import mysqlsh


def generate_patients_data(num_rows):
  # read datasets
  # names and genders
  female_names = pandas.read_csv(
    "top-350-male-and-female-names-since-1848-2019-02-26.csv", 
    usecols = ["Female Name"]
  ).rename(columns = {'Female Name': 'name'})
  female_names['gender'] = (['F']*female_names.count()['name'])
  male_names = pandas.read_csv(
    "top-350-male-and-female-names-since-1848-2019-02-26.csv", 
    usecols = ["Male Name"]
  ).rename(columns = {'Male Name': 'name'})
  male_names['gender'] = (['M']*male_names.count()['name'])
  names = pandas.concat([female_names, male_names], ignore_index=True)
  surnames = pandas.read_csv(
    "Names_2010Census.csv", 
    usecols=['name'], skipfooter=1, engine='python'
  ).rename(columns={'name': 'surname'})
  # diagnosises
  diagnosises = pandas.read_csv('diagnosis.csv')
  # Possible results
  results = pandas.DataFrame({
    "result": ["R", "N", "D"], 
    "frequency": [6,3,1]
  })
  # Start building data
  diagnosises = diagnosises.sample(
    num_rows, replace=True, 
    weights=diagnosises['frequency']
  ).set_index(pandas.Series(range(num_rows)))
  results = results.sample(
    num_rows, replace=True, 
    weights=results['frequency']
  ).set_index(pandas.Series(range(num_rows)))
  names=names.sample(
    num_rows, replace=True
  ).set_index(pandas.Series(range(num_rows)))
  surnames=surnames.sample(
    num_rows, replace=True
  ).set_index(pandas.Series(range(num_rows)))
  # Get table object
  patients=mysqlsh.globals.session.get_schema('cookbook').get_table('patients')
  # Loop, inserting rows
  for i in range(num_rows):
    national_id = str(random.randrange(10,99)) + \
      ''.join(random.sample(string.ascii_uppercase, 2)) + \
      str(random.randrange(100000, 999999))
    age = random.randrange(15, 99)
    date_arrived = datetime.strptime('2020-01-01', '%Y-%m-%d') + \
      timedelta(days=random.randrange(365))
    date_departed = date_arrived + timedelta(days=random.randrange(60))
    date_arrived = date_arrived.strftime('%Y-%m-%d')
    date_departed = date_departed.strftime('%Y-%m-%d')
    name = names['name'][i]
    gender = names['gender'][i]
    surname = surnames['surname'][i]
    result = results['result'][i]
    diagnosis = diagnosises['diagnosis'][i]
    patients.insert(
      'national_id', 'name', 'surname', 
      'gender', 'age', 'diagnosis', 
      'result', 'date_arrived', 'date_departed'
    ).values(
      national_id, name, surname, 
      gender, age, diagnosis, 
      result, date_arrived, date_departed
    ).execute()
  
