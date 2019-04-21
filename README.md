# POOC_Project
Projet de programmation C++ pour Paris 1, Martin Viellard et Elias Tazartes

Please when submitting, send me an e-mail with the following information:
•  name, surname, master track, student id of each team member
•  all team members should be on carbon copy
•  link toGitHubrepository containing the project, this is the only means I accept it.


Note that GitHubGist is a way for quick share of pieces of code and notes, and is not equivalentto GitHub repository. 
Thus, it will not be accepted as means of project submission

The task at hand :
Write a program that produces loan payment schedule, ideally in the form of a CSV output file,given the following input sets:

•  Fixed principal payments, and–fixed interest rate–margin + parametrised, normally distributed floating interest rate

•  Fixed interest rate and instalments, given:

–n,PV,r
–PMT,n,r
–PMT,PV,r
–PMT,n,PV

Notice that in all 4 cases, you can calculate the missing parameter from the remaining ones. For all elements except for r, there is a closed form formula.  For r, you have to set up an optimisation algorithm. You should create a comprehensive program, that takes all the cases into account and prepares an output schedule.  Your program should be intuitive and user friendly.  It should be robust to user errors, such as providing nonsense input - the program ought to guide how to provide the data correctly and foresee alternative path rather than calculate nonsense output.

When asking for interest rate, user should provide it in yearly terms.  The program should compute the appropriate rate based on frequency.  Assume only the following frequencies: yearly,semi-annually, quarterly, monthly.  Having this, and loan start date, you can build schedule that provides specific date - month and year will be sufficient, you don’t have to provide full date - rather than an ordinal number of a period. 
