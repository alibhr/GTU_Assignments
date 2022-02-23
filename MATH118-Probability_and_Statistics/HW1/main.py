import numpy as np
import pandas as pd

all_results = []
pd.set_option("display.max_rows", None, "display.max_columns", None)
data_frame = pd.read_csv("owid-covid-data.csv")
location_list = list(data_frame["location"])

# 1. How many countries the dataset has?
location_set = set(data_frame["location"])
#print("Q1:", end = ' ')
print(len(location_set))

# 2. When is the earliest date data are taken for a country? Which country is it?
grouped_location = data_frame.groupby("location")
dates = grouped_location.agg(date=('date', np.min))
min_date = dates.min()
print(dates[dates.eq(min_date).any(True)])

# 3. How many cases are confirmed for each country so far? Print pairwise results of country and total cases.
result_df = grouped_location.agg(total_case=("total_cases", np.max))
all_results.append(result_df)
#print(result_df)

# 4. How many deaths are confirmed for each country so far? Print pairwise results of country and total deaths.
result_df = grouped_location.agg(total_deaths=("total_deaths", np.max))
all_results.append(result_df)
#print(result_df)

# 5. What are the average, minimum, maximum and variation values of the reproduction rates for each country?
column_name = "reproduction_rate"
result_df = grouped_location.agg(q5_min=(column_name, np.min), q5_max=(column_name, np.max), q5_avg=(column_name, np.mean), q5_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 6. What are the average, minimum, maximum and variation values of the icu patients (intensive care unit patients) for each country?
column_name = "icu_patients"
result_df = grouped_location.agg(q6_min=(column_name, np.min), q6_max=(column_name, np.max), q6_avg=(column_name, np.mean), q6_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 7. What are the average, minimum, maximum and variation values of the hosp patients (hospital patients) for each country?
column_name = "hosp_patients"
result_df = grouped_location.agg(q7_min=(column_name, np.min), q7_max=(column_name, np.max), q7_avg=(column_name, np.mean), q7_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 8. What are the average, minimum, maximum and variation values of the weekly icu (intensive care unit) admissions for each country?
column_name = "weekly_icu_admissions"
result_df = grouped_location.agg(q8_min=(column_name, np.min), q8_max=(column_name, np.max), q8_avg=(column_name, np.mean), q8_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 9. What are the average, minimum, maximum and variation values of the weekly hospital admissions for each country?
column_name = "weekly_hosp_admissions"
result_df = grouped_location.agg(q9_min=(column_name, np.min), q9_max=(column_name, np.max), q9_avg=(column_name, np.mean), q9_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 10. What are the average, minimum, maximum and variation values of new tests per day for each country?
column_name = "new_tests"
result_df = grouped_location.agg(q10_min=(column_name, np.min), q10_max=(column_name, np.max), q10_avg=(column_name, np.mean), q10_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 11. How many tests are conducted in total for each country so far?
column_name = "total_tests"
result_df = grouped_location.agg(q11_min=(column_name, np.min), q11_max=(column_name, np.max), q11_avg=(column_name, np.mean), q11_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 12. What are the average, minimum, maximum and variation values of the positive rates of the tests for each country?
column_name = "positive_rate"
result_df = grouped_location.agg(q12_min=(column_name, np.min), q12_max=(column_name, np.max), q12_avg=(column_name, np.mean), q12_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 13. What are the average, minimum, maximum and variation values of the tests per case for each country?
column_name = "tests_per_case"
result_df = grouped_location.agg(q13_min=(column_name, np.min), q13_max=(column_name, np.max), q13_avg=(column_name, np.mean), q13_var=(column_name, np.var))
all_results.append(result_df)
#print(result_df)

# 14. How many people are vaccinated by at least one dose in each country?
result_df = grouped_location.agg(vaccinated_by_at_least_one=("people_vaccinated", np.max))
all_results.append(result_df)
#print(result_df)

# 15. How many people are vaccinated fully in each country?
result_df = grouped_location.agg(vaccinated_fully=("people_fully_vaccinated", np.max))
all_results.append(result_df)
#print(result_df)

# 16. How many vaccinations are administered in each country so far?
result_df = grouped_location.agg(total=("total_vaccinations", np.max))
all_results.append(result_df)
#print(result_df)

# 17. List information about 
'''
    population,
    median age,
    # of people aged 65 older,
    # of people aged 70 older,
    economic performance,
    death rates due to heart disease,
    diabetes prevalence,
    # of female smokers,
    # of male smokers,
    handwashing facilities,
    hospital beds per thousand people,
    life expectancy and human
    development index.
'''
df_list = [
    grouped_location.agg(population                 =   ("population",                 np.max)),
    grouped_location.agg(median_age                 =   ("median_age",                 np.max)),
    grouped_location.agg(aged_65_older              =   ("aged_65_older",              np.max)),
    grouped_location.agg(aged_70_older              =   ("aged_70_older",              np.max)),
    grouped_location.agg(gdp_per_capita             =   ("gdp_per_capita",             np.max)),
    grouped_location.agg(cardiovasc_death_rate      =   ("cardiovasc_death_rate",      np.max)),
    grouped_location.agg(diabetes_prevalence        =   ("diabetes_prevalence",        np.max)),
    grouped_location.agg(female_smokers             =   ("female_smokers",             np.max)),
    grouped_location.agg(male_smokers               =   ("male_smokers",               np.max)),
    grouped_location.agg(handwashing_facilities     =   ("handwashing_facilities",     np.max)),
    grouped_location.agg(hospital_beds_per_thousand =   ("hospital_beds_per_thousand", np.max)),
    grouped_location.agg(life_expectancy            =   ("life_expectancy",            np.max)),
    grouped_location.agg(human_development_index    =   ("human_development_index",    np.max))
]
result_df = pd.concat(df_list, axis=1)
all_results.append(result_df)
#print(result_df)

# 18. Summarize all the results that you obtain by the first 17 questions (except question 2).
result_df = pd.concat(all_results, axis=1)
result_df.to_csv("output.csv")
#print(result_df)

