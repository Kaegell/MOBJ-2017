#Question 1
	- cf. code

#Question 2
	- Les constructeurs ont besoin d'etre publiques. Sinon, ils sont innaccessibles de l'exterieur de la classe

#Question 3
	- cf. code (isEmpty() est un one-liner)

#Question 4
	- On surcharge operator<< en non-membre (dans Main.cpp)
	- On surcharge operator&& en membre (dans la classe Box).
Le compilateur interpretera le symbole and comme &&, et la
surcharge d'operateur fonctionnera.

#Question 5
	- Utilisation d'une variable statique et d'une methode
statique.

#Question Facultative : tme1Qf
	1) On peut utiliser la classe avec ses attributs telles
qu'elles et adapter les accesseurs getX1, getX2, getY1, getY2.
	2) On peut sinon utiliser la classe avec un design 
pattern DPAdapter, pour lui faire adopter un comportement 
analogue a la classe Box
