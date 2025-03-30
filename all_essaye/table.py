def table_verite(fonction, variables):
  """
  Affiche la table de vérité d'une fonction booléenne.

  Args:
    fonction: Une fonction booléenne prenant en argument une liste de valeurs booléennes et renvoyant une valeur booléenne.
    variables: Une liste des noms des variables booléennes de la fonction.

  Exemple:
  >>> table_verite(lambda x, y: x and not y, ["x", "y"])
  | x | y | f(x, y) |
  |---|---|---|
  | 0 | 0 | 1 |
  | 0 | 1 | 0 |
  | 1 | 0 | 1 |
  | 1 | 1 | 0 |
  """
  # Génère toutes les combinaisons possibles de valeurs booléennes pour les variables.
  combinaisons = [(v1, v2) for v1 in [0, 1] for v2 in [0, 1]]

  # En-tête de la table de vérité
  print("|", " | ".join(variables + ["f({})".format(", ".join(variables))]), "|")
  print("|", "-" * len("|".join(variables + ["f({})".format(", ".join(variables))])), "|")

  # Affiche chaque ligne de la table de vérité
  for combinaison in combinaisons:
    valeurs_entrees = [combinaison[i] for i in range(len(variables))]
    valeur_sortie = fonction(*valeurs_entrees)
    print("|", " | ".join([str(valeur) for valeur in valeurs_entrees + [valeur_sortie]]), "|")

def forme_canonique(fonction, variables):
  """
  Calcule la première forme canonique (somme de produits) d'une fonction booléenne.

  Args:
    fonction: Une fonction booléenne prenant en argument une liste de valeurs booléennes et renvoyant une valeur booléenne.
    variables: Une liste des noms des variables booléennes de la fonction.

  Exemple:
  >>> forme_canonique(lambda x, y: x and not y, ["x", "y"])
  (x and not y)
  """
  # Génère toutes les combinaisons possibles de valeurs booléennes pour les variables.
  combinaisons = [(v1, v2) for v1 in [0, 1] for v2 in [0, 1]]

  # Termes de la première forme canonique
  termes = []

  # Itère sur toutes les combinaisons de valeurs booléennes
  for combinaison in combinaisons:
    # Si la fonction est vraie pour cette combinaison, créez un terme
    if fonction(*combinaison):
      terme = []
      for i, valeur in enumerate(combinaison):
        if valeur == 0:
          terme.append("not {}".format(variables[i]))
        else:
          terme.append(variables[i])
      termes.append(" and ".join(terme))

  # Combine les termes en une expression logique
  if termes:
    return " or ".join(termes)
  else:
    return "0"  # La fonction est toujours fausse

def forme_canonique_seconde(fonction, variables):
  """
  Calcule la seconde forme canonique (produit de sommes) d'une fonction booléenne.

  Args:
    fonction: Une fonction booléenne prenant en argument une liste de valeurs booléennes et renvoyant une valeur booléenne.
    variables: Une liste des noms des variables booléennes de la fonction.

  Exemple:
  >>> forme_canonique_seconde(lambda x, y: x and not y, ["x", "y"])
  (not x or y) and (x or not y)
  """
  # Génère toutes les combinaisons possibles de valeurs booléennes pour les variables.
  combinaisons = [(v1, v2) for v1 in [0, 1] for v2 in [0, 1]]

  # Clauses de la seconde forme canonique
  clauses = []

  # Itère sur toutes les combinaisons de valeurs booléennes
  for combinaison in combinaisons:
    # Si la fonction est fausse pour cette combinaison, créez une clause
    if not fonction(*combinaison):
      clause = []
  # Suite du code pour la seconde forme canonique
      for i, valeur in enumerate(combinaison):
        if valeur == 0:
          clause.append(variables[i])
        else:
          clause.append("not {}".format(variables[i]))
      clauses.append(" or ".join(clause))

  # Combine les clauses en une expression logique
  if clauses:
    return " and ".join(clauses)
  else:
    return "1"  # La fonction est toujours vraie

# Exemple d'utilisation
fonction = lambda x, y: x and not y  # Fonction AND et NOT
variables = ["x", "y"]

table_verite(fonction, variables)
print("\nPremière forme canonique:", forme_canonique(fonction, variables))
print("Seconde forme canonique:", forme_canonique_seconde(fonction, variables))

