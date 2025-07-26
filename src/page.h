#pragma once

#include <Arduino.h>

const char code[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>YoupiLight</title>
</head>
<body>
    <header>
        <h1>YoupiLight</h1>
        <nav>
            <ul>
                <li><a href="#reglage">Réglages</a></li>
                <li><a href="#commandes">Commandes</a></li>
            </ul>
        </nav>
    </header>
    <main>
        <section id="time">
            <h2>Heure locale</h2>
            <p><span id="heure">---</span> : <span id="minute">---</span> : <span id="seconde">---</span></p>
        </section>
        
    </main>
    <script defer>
        async function getData(url) {
            try {
                const response = await fetch(url);
                if(!response.ok) {
                    throw new Error(`Erreur HTTP : ${response.status}`);
                }
                const data = await response.json();
                console.log('Données récupérées : ',data);
                return data
            }
            catch (err) {
                console.log("Erreur lors de la récupération des données", err);
            }
        }
        /* ===== Récupération des éléments du DOM pour l'affichage du temps ===== */
        const heureEl = document.getElementById('heure');
        const minuteEl = document.getElementById("minute");
        const secondeEl = document.getElementById("seconde");
        let url_time = '/time';

        // Récupération de l'heure depuis l'api
        // Il faut attendre que la promesse soit résolue pour accéder aux données
        async function displayTime() { // Créez une fonction asynchrone pour utiliser await
            const dataObject = await getData(url_time); // Utilisez await ici

            if (dataObject) { // Vérifiez si dataObject n'est pas undefined (en cas d'erreur de récupération)
                // Injection des données du temps
                let minute = dataObject.minute;
                let heure = dataObject.heure;
                let seconde = dataObject.seconde;

                heureEl.textContent = heure || "---";
                minuteEl.textContent = minute || "---";
                secondeEl.textContent = seconde || "---";
            }
        }

        displayTime(); // Appelez la fonction pour afficher l'heure
    </script>
</body>
</html>
)rawliteral";

/*
AT                       // Test communication
AT+CPIN?                 // Vérifie si la carte SIM est prête
AT+CSQ                   // Vérifie le niveau du signal
AT+CREG?                 // Vérifie l'enregistrement réseau
AT+SAPBR=3,1,"CONTYPE","GPRS"     // Définit le mode de connexion
AT+SAPBR=3,1,"APN","internet"     // Remplace "internet" par l’APN de ton opérateur
AT+SAPBR=1,1                      // Ouvre la connexion GPRS
AT+SAPBR=2,1                      // Vérifie l’état de la connexion
AT+HTTPINIT                      // Initialise HTTP
AT+HTTPPARA="CID",1              // Définit le profil de connexion
AT+HTTPPARA="URL","http://api.example.com/data"
AT+HTTPACTION=0                  // 0 = GET, 1 = POST
AT+HTTPREAD                      // Lit la réponse du serveur
AT+HTTPTERM                      // Termine la session HTTP
*/