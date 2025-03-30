#include <iostream>
#include <pqxx/pqxx>
#include <string>
int main() {
    try {
        // Connexion à la base de données
        pqxx::connection conn("dbname=mit user=postgres password=m hostaddr=127.0.0.1 port=5432");

        // Vérifie si la connexion est établie avec succès
        if (conn.is_open()) {
            std::cout << "Connexion à la base de données réussie." << std::endl;
        } else {
            std::cout << "Erreur lors de la connexion à la base de données." << std::endl;
            return 1;
        }

        // Exécution d'une requête SQL
        pqxx::work txn(conn);
	
	std::string nom = "ANDRIAMANDRATOMANANA";
	std::string prenom = "Narindrantsoa";
	std::string eth = "8c:c1:21:50:27:59";
	std::string lan = "e0:3d:31:08:83:70";
	std::string serie= "3LKCB89964";
	std::string pan = "PAN-01007";
	std::string ip = "192.168.1.4";
	std::string niveau = "L1";

	std::string query = "INSERT INTO Etudiant (nom, prenom, mac_eth,mac_lan, serie, pan, ip, niveau) VALUES ('" + nom + "', '" + prenom + "','" + eth + "','" + lan + "', '" + serie + "', '" + pan + "','" + ip + "','" + niveau + "')";
        
	txn.exec(query);
	pqxx::result result = txn.exec("SELECT * FROM Etudiant");

        // Parcourir les résultats de la requête
        for (const auto& row : result) {
            // Afficher les données de chaque ligne
            std::cout << "ID : " << row[0].as<int>() << ", nom : " << row[1].as<std::string>() << std::endl;
        }

        // Valider et appliquer les changements à la base de données
        txn.commit();

        // Fermer la connexion
        conn.disconnect();
    } catch (const std::exception &e) {
        // Gérer les exceptions
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
