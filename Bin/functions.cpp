
//will be used for time comparisons.
long deciTime(int day, int hour, int minute)  //take in day of the week, hour and minute
{
    long deciTime = 0;

    deciTime = day * 86400;
    deciTime = deciTime + hour * 3600;
    deciTime = deciTime + minute * 60;

    return deciTime;  //returns a decimal value for the day and time in terms of seconds
}

void viewSchedule()
{
    for(vector<int>::iterator ptr = classes.begin(); ptr != classes.end(); ptr++){
        //take crn and lookup in database
        //return class info (students, time, etc)
    }
}