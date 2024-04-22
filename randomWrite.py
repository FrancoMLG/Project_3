import random

school_conference = ["Appalachian State University_Sun Belt Conference",
"Arizona State University_Pac-12 Conference",
"Arkansas State University_Sun Belt Conference",
"Auburn University_Southeastern Conference",
"Ball State University_Mid-American Conference",
"Baylor University_Big 12 Conference",
"Boise State University_Mountain West Conference",
"Boston College_Atlantic Coast Conference",
"Bowling Green State University_Mid-American Conference",
"Brigham Young University_Big 12 Conference",
"California State University, Fresno_Mountain West Conference",
"Central Michigan University_Mid-American Conference",
"Clemson University_Atlantic Coast Conference",
"Coastal Carolina University_Sun Belt Conference",
"Colorado State University_Mountain West Conference",
"Duke University_Atlantic Coast Conference",
"East Carolina University_American Athletic Conference",
"Eastern Michigan University_Mid-American Conference",
"Florida Atlantic University_American Athletic Conference",
"Florida International University_Conference USA",
"Florida State University_Atlantic Coast Conference",
"Georgia Institute of Technology_Atlantic Coast Conference",
"Georgia Southern University_Sun Belt Conference",
"Georgia State University_Sun Belt Conference",
"Indiana University, Bloomington_Big Ten Conference",
"Iowa State University_Big 12 Conference",
"Jacksonville State University_Conference USA",
"James Madison University_Sun Belt Conference",
"Kansas State University_Big 12 Conference",
"Kent State University_Mid-American Conference",
"Liberty University_Conference USA",
"Louisiana State University_Southeastern Conference",
"Louisiana Tech University_Conference USA",
"Marshall University_Sun Belt Conference",
"Miami University (Ohio)_Mid-American Conference",
"Michigan State University_Big Ten Conference",
"Middle Tennessee State University_Conference USA",
"Mississippi State University_Southeastern Conference",
"New Mexico State University_Conference USA",
"North Carolina State University_Atlantic Coast Conference",
"Northern Illinois University_Mid-American Conference",
"Northwestern University_Big Ten Conference",
"Ohio University_Mid-American Conference",
"Oklahoma State University_Big 12 Conference",
"Old Dominion University_Sun Belt Conference",
"Oregon State University_Pac-12 Conference",
"Pennsylvania State University_Big Ten Conference",
"Purdue University_Big Ten Conference",
"Rice University_American Athletic Conference",
"Rutgers, The State University of New Jersey, New Brunswick_Big Ten Conference",
"Sam Houston State University_Conference USA",
"San Diego State University_Mountain West Conference",
"San Jose State University_Mountain West Conference",
"Southern Methodist University_American Athletic Conference",
"Stanford University_Pac-12 Conference",
"Syracuse University_Atlantic Coast Conference",
"Temple University_American Athletic Conference",
"Texas A&M University, College Station_Southeastern Conference",
"Texas Christian University_Big 12 Conference",
"Texas State University_Sun Belt Conference",
"Texas Tech University_Big 12 Conference",
"The Ohio State University_Big Ten Conference",
"The University of North Carolina at Charlotte_American Athletic Conference",
"The University of Southern Mississippi_Sun Belt Conference",
"The University of Tulsa_American Athletic Conference",
"Troy University_Sun Belt Conference",
"Tulane University_American Athletic Conference",
"U.S. Air Force Academy_Mountain West Conference",
"U.S. Military Academy_Independent",
"U.S. Naval Academy_American Athletic Conference",
"University at Buffalo, the State University of New York_Mid-American Conference",
"University of Akron_Mid-American Conference",
"University of Alabama_Southeastern Conference",
"University of Alabama at Birmingham_American Athletic Conference",
"University of Arizona_Pac-12 Conference",
"University of Arkansas, Fayetteville_Southeastern Conference",
"University of California, Berkeley_Pac-12 Conference",
"University of California, Los Angeles_Pac-12 Conference",
"University of Central Florida_Big 12 Conference",
"University of Cincinnati_Big 12 Conference",
"University of Colorado, Boulder_Pac-12 Conference",
"University of Connecticut_Independent",
"University of Florida_Southeastern Conference",
"University of Georgia_Southeastern Conference",
"University of Hawaii, Manoa_Mountain West Conference",
"University of Houston_Big 12 Conference",
"University of Illinois Urbana-Champaign_Big Ten Conference",
"University of Iowa_Big Ten Conference",
"University of Kansas_Big 12 Conference",
"University of Kentucky_Southeastern Conference",
"University of Louisiana at Lafayette_Sun Belt Conference",
"University of Louisiana Monroe_Sun Belt Conference",
"University of Louisville_Atlantic Coast Conference",
"University of Maryland, College Park_Big Ten Conference",
"University of Massachusetts, Amherst_Independent",
"University of Memphis_American Athletic Conference",
"University of Miami (Florida)_Atlantic Coast Conference",
"University of Michigan_Big Ten Conference",
"University of Minnesota, Twin Cities_Big Ten Conference",
"University of Mississippi_Southeastern Conference",
"University of Missouri, Columbia_Southeastern Conference",
"University of Nebraska-Lincoln_Big Ten Conference",
"University of Nevada, Las Vegas_Mountain West Conference",
"University of Nevada, Reno_Mountain West Conference",
"University of New Mexico_Mountain West Conference",
"University of North Carolina, Chapel Hill_Atlantic Coast Conference",
"University of North Texas_American Athletic Conference",
"University of Notre Dame_Independent",
"University of Oklahoma_Big 12 Conference",
"University of Oregon_Pac-12 Conference",
"University of Pittsburgh_Atlantic Coast Conference",
"University of South Alabama_Sun Belt Conference",
"University of South Carolina, Columbia_Southeastern Conference",
"University of South Florida_American Athletic Conference",
"University of Southern California_Pac-12 Conference",
"University of Tennessee, Knoxville_Southeastern Conference",
"University of Texas at Austin_Big 12 Conference",
"University of Texas at El Paso_Conference USA",
"University of Texas at San Antonio_American Athletic Conference",
"University of Toledo_Mid-American Conference",
"University of Utah_Pac-12 Conference",
"University of Virginia_Atlantic Coast Conference",
"University of Washington_Pac-12 Conference",
"University of Wisconsin-Madison_Big Ten Conference",
"University of Wyoming_Mountain West Conference",
"Utah State University_Mountain West Conference",
"Vanderbilt University_Southeastern Conference",
"Virginia Polytechnic Institute and State University_Atlantic Coast Conference",
"Wake Forest University_Atlantic Coast Conference",
"Washington State University_Pac-12 Conference",
"West Virginia University_Big 12 Conference",
"Western Kentucky University_Conference USA",
"Western Michigan University_Mid-American Conference"]

positions = ["C", "OG", "OT", "QB", "RB", "WR", "TE", "DT", "NT", "DE", "MLB", "OLB", "CB", "S", "K", "P", "LS"]

with open("school_conferenceList.txt", "w") as file:
    for i in range(100000):
        random_string = random.choice(school_conference )
        if i == 99999:
            file.write(random_string)
        else:
            file.write(random_string + "\n")
file.close()

with open("positionList.txt", "w") as file:
    for i in range(100000):
        random_string = random.choice(positions)
        if i == 99999:
            file.write(random_string)
        else:
            file.write(random_string + "\n")
file.close()
