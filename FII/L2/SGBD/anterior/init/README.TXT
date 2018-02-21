1. Intrati in contul de admin din Oracle SQL si executati 
   scriptul create_user. Acesta va elimina userul student
   creat in semestrul trecut (daca exista) si va crea altul
   cu mai mult spatiu de stocare pe disc.
   
2. Executati scriptul import.bat (trebuie sa fie langa 
   "bd.dmp" ca sa functioneze ok).
   
3. Mergeti in contul student/STUDENT si executati comanda
   "select table_name from user_tables;"
   
   
Ar trebui sa vedeti 7 tabele:
 
answers    (12839 randuri)
chapters   (6)
deleted_questions (486)
question_cache (1495)
questions (5306)
reports (6481)
users (515)

Deocamdata va las pe voi sa va prindeti ce inseamna fiecare 
camp de pe acolo, cert este ca vom construi mai multe
in acest semestru in jurul acestei baze de date.