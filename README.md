# Amazon-account-manager

You were hired to write a program that manages amazon accounts

Before accessing the interface, the user must either login or signup 

1)	Log in:
The user must enter the email and password. Your program must check if the user exists (you will be provided with an input file (“database.txt”) that contains 3 users to start with). A user exists if the email and the password entered match the ones in the file. If by mistake, the user mistyped the password by inverting 2 consecutive characters, you must ask him the secret question which is available in the file and check the answer with the one provided too. Also, if the email entered does not match one of those available in the file, you should direct the user to the signup menu.
2)	 Signup Menu:

The user is prompted to enter all the information as shown in the input file. When entering the information, if the user enters an existing email or bank account number available in the output.txt file, he will be informed that the information already exists in the records file and needs to enter different ones.
3)	Logout Program:

When the user decides to exit the program 1 output file is created. It is similar to the input file except that it contains the updated information (the updated password, new users, etc.) and it is alphabetically sorted by family name. This file must be named: output.txt.
 
Once signed in, your program must interact with the user in a loop that allows the user to perform the following actions
1)	Change user information

The user will be introduced to a page where he/ she can change any information in their profile (profile names, password, email, account number-banking account) and the information must be updated to the user profile. Before any change to the profile, the user MUST be asked to re-authenticate by reentering the password only.
2)	Make order
Take into consideration that Amazon offers specific types of product for clients to
  purchase. See the list below for the available products along with their prices:
•	Book: 200 MAD
•	Skin care: 700 MAD
•	Watch: 1000 MAD
•	Desk: 4000 MAD
•	Laptop: 6000 MAD
Your program should get the order of the client along with the quantity and keep on asking as long as the client wishes to keep on purchasing. 
3)	Complete order

Once done, the program should deduct the amount of the purchase from the user’s balance. In case the balance is not enough, the user will be asked to enter another bank account, and then check if the new entered account has enough money in the balance to pay for the order. If the balance is enough, you should update the user information with this new bank account. In case it is not, you should keep on asking the user, for a maximum of three times, to enter a bank account and each time check if the balance of that account is enough to pay for the order. If by the third attempt, the balance of the entered bank account is not enough, the order is dropped.

4) Delete account
The user can decide to delete his account when he wants. When doing so, you should delete all user information.



Note:
The file database.txt contains in every row the profile information of a user which includes: Email fname lname password bank_account_number balance secret_question answer 
