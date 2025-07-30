#pragma once
#include <Arduino.h>
const char code[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>YoupiLight</title>
    <style>
        :root {
            --primary-color: #4a6fa5;
            --secondary-color: #166088;
            --accent-color: #4fc3f7;
            --background-color: #f8f9fa;
            --text-color: #333;
            --light-text: #fff;
            --border-radius: 8px;
            --box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
            --transition: all 0.3s ease;
            --error-color: #e53935;
            --success-color: #43a047;
            --on-color: #4CAF50;
            --off-color: #F44336;
            --loading-color: #9E9E9E;
        }

        * {
            margin: 0;
            padding: 0;
            box-sizing: border-box;
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
        }

        body {
            background-color: var(--background-color);
            color: var(--text-color);
            line-height: 1.6;
            min-height: 100vh;
            display: flex;
            flex-direction: column;
        }

        header {
            background-color: var(--primary-color);
            color: var(--light-text);
            padding: 1.5rem;
            text-align: center;
            box-shadow: var(--box-shadow);
        }

        h1 {
            font-size: 2rem;
            font-weight: 600;
        }

        h2 {
            font-size: 1.5rem;
            margin-bottom: 1rem;
            color: var(--secondary-color);
            border-bottom: 2px solid var(--accent-color);
            padding-bottom: 0.5rem;
        }

        main {
            flex: 1;
            max-width: 1200px;
            margin: 2rem auto;
            padding: 0 1.5rem;
            width: 100%;
        }

        .grid-container {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 2rem;
            margin-bottom: 2rem;
        }

        section {
            background-color: white;
            border-radius: var(--border-radius);
            padding: 1.5rem;
            box-shadow: var(--box-shadow);
        }

        #heure, #minute, #seconde {
            font-size: 2rem;
            font-weight: bold;
            color: var(--primary-color);
        }

        #etat_lampe {
            font-weight: bold;
            padding: 0.3rem 0.5rem;
            border-radius: var(--border-radius);
            color: white;
        }

        .form-row {
            display: grid;
            grid-template-columns: repeat(auto-fit, minmax(300px, 1fr));
            gap: 2rem;
        }

        fieldset {
            border: 1px solid #ddd;
            border-radius: var(--border-radius);
            padding: 1.5rem;
            margin-bottom: 1rem;
        }

        legend {
            font-weight: bold;
            padding: 0 0.5rem;
            color: var(--secondary-color);
        }

        label {
            display: block;
            margin-bottom: 0.5rem;
            font-weight: 500;
        }

        input[type="datetime-local"] {
            width: 100%;
            padding: 0.75rem;
            border: 1px solid #ddd;
            border-radius: var(--border-radius);
            margin-bottom: 1rem;
            font-size: 1rem;
        }

        button {
            color: white;
            border: none;
            padding: 0.75rem 1.5rem;
            border-radius: var(--border-radius);
            cursor: pointer;
            font-size: 1rem;
            font-weight: 500;
            transition: var(--transition);
            width: 100%;
            margin-top: 0.5rem;
        }

        button:hover:not(:disabled) {
            transform: translateY(-2px);
            opacity: 0.9;
        }

        button:disabled {
            cursor: not-allowed;
            transform: none;
            opacity: 0.7;
        }

        #btn-Lampe {
            background-color: var(--loading-color);
        }

        #btn-Lampe.on-state {
            background-color: var(--off-color);
        }

        #btn-Lampe.off-state {
            background-color: var(--on-color);
        }

        #btn_reglage {
            background-color: var(--primary-color);
        }

        #btn_reglage:hover:not(:disabled) {
            background-color: var(--secondary-color);
        }

        #toast {
            position: fixed;
            top: 20px;
            right: 20px;
            padding: 15px 20px;
            border-radius: var(--border-radius);
            color: white;
            font-weight: 500;
            opacity: 0;
            transition: var(--transition);
            z-index: 1000;
        }

        .toast-success {
            background-color: var(--success-color);
        }

        .toast-error {
            background-color: var(--error-color);
        }

        .state-loading {
            background-color: var(--loading-color);
        }

        .state-on {
            background-color: var(--on-color);
        }

        .state-off {
            background-color: var(--off-color);
        }

        footer {
            text-align: center;
            padding: 1.5rem;
            background-color: var(--primary-color);
            color: var(--light-text);
            margin-top: auto;
        }

        @media (max-width: 768px) {
            .form-row {
                grid-template-columns: 1fr;
            }
            
            .grid-container {
                grid-template-columns: 1fr;
            }
        }
    </style>
</head>
<body>
    <header>
        <h1>YOUPILIGHT</h1>
    </header>
    <main>
        <div class="grid-container">
            <section>
                <h2>Heure actuelle</h2>
                <p><span id="heure">--</span> : <span id="minute">--</span> : <span id="seconde">--</span></p>
            </section>
            <section id="commandes">
                <h2>Commande de la lampe</h2>
                <article>
                    <p>État de la lampe : <span id="etat_lampe" class="state-loading">Chargement...</span></p>
                    <button id="btn-Lampe" disabled>Chargement...</button>
                </article>
            </section>
        </div>
        <section id="reglages">
            <h2>Réglages horaires</h2>
            <form id="config-form">
                <div class="form-row">
                    <fieldset>
                        <legend><strong>Allumage</strong></legend>
                        <label for="on_config">Date/Heure</label>
                        <input type="datetime-local" id="on_config" required>
                    </fieldset>
                    <fieldset>
                        <legend><strong>Extinction</strong></legend>
                        <label for="off_config">Date/Heure</label>
                        <input type="datetime-local" id="off_config" required>
                    </fieldset>
                </div>
                <button type="submit" id="btn_reglage">Envoyer le réglage</button>
            </form>
        </section>
    </main>
    <div id="toast"></div>
    <footer>
        <p>&copy; YoupiLight - 2025 - Tous droits réservés</p>
    </footer>

    <script>
        // ===== CONFIGURATION =====
        const ESP_IP = "192.168.4.1"; // IP par défaut ESP en mode AP
        const BASE_URL = `http://${ESP_IP}`;
        const DEBUG = true;

        // ===== ÉLÉMENTS DU DOM =====
        const etatLampeEl = document.getElementById('etat_lampe');
        const btnLampeEl = document.getElementById('btn-Lampe');
        const btnReglageEl = document.getElementById('btn_reglage');

        // ===== ÉTAT APPLICATION =====
        let lampeState = null; // null = état inconnu, true = allumé, false = éteint

        // ===== FONCTIONS UTILITAIRES =====
        function logDebug(...args) {
            if (DEBUG) console.log('[DEBUG]', ...args);
        }

        function showToast(message, type = 'success') {
            const toast = document.getElementById('toast');
            toast.textContent = message;
            toast.className = `toast-${type}`;
            toast.style.opacity = 1;
            
            setTimeout(() => {
                toast.style.opacity = 0;
            }, 3000);
        }

        function padZero(num) {
            return num < 10 ? `0${num}` : num;
        }

        // ===== FONCTIONS DE CONFIGURATION =====
        function parseDataToInt(data) {
            const parsed = parseInt(data, 10);
            return isNaN(parsed) ? 0 : parsed;
        }

        function splitInputAndParseToInt(input) {
            if (!input || !input.value) {
                throw new Error('Veuillez remplir tous les champs');
            }
            
            const [date, time] = input.value.split('T');
            if (!date || !time) {
                throw new Error('Format datetime invalide. Attendu: YYYY-MM-DDTHH:MM');
            }

            const [year, month, day] = date.split('-').map(Number);
            const [hour, minute] = time.split(':').map(Number);
            const seconde = 0;
            
            return {
                annee: parseDataToInt(year),
                mois: parseDataToInt(month),
                jour: parseDataToInt(day),
                heure: parseDataToInt(hour),
                minute: parseDataToInt(minute),
                seconde: parseDataToInt(seconde)
            };
        }

        // ===== GESTION DE L'AFFICHAGE =====
        function updateUIState() {
            // Mettre à jour l'affichage du bouton
            if (lampeState === null) {
                btnLampeEl.textContent = "Chargement...";
                btnLampeEl.className = "";
                btnLampeEl.disabled = true;
                etatLampeEl.textContent = "Chargement...";
                etatLampeEl.className = "state-loading";
            } else {
                btnLampeEl.textContent = lampeState ? "Éteindre" : "Allumer";
                btnLampeEl.className = lampeState ? "on-state" : "off-state";
                btnLampeEl.disabled = false;
                etatLampeEl.textContent = lampeState ? "Allumée" : "Éteinte";
                etatLampeEl.className = lampeState ? "state-on" : "state-off";
            }
        }

        // ===== GESTION DE LA LAMPE =====
        async function toggleLampe() {
            if (lampeState === null) return;
            
            btnLampeEl.disabled = true;
            const newState = !lampeState;
            
            try {
                const response = await fetch(`${BASE_URL}/lampe`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify({ state: newState })
                });
                
                if (!response.ok) throw new Error('Erreur réseau');
                
                const result = await response.json();
                logDebug('Réponse lampe:', result);
                
                lampeState = newState;
                updateUIState();
                showToast(`Lampe ${newState ? 'allumée' : 'éteinte'} avec succès`);
                
            } catch (err) {
                logDebug('Erreur lampe:', err);
                showToast('Erreur de commande', 'error');
            } finally {
                btnLampeEl.disabled = false;
            }
        }

        async function checkLampeState() {
            try {
                const response = await fetch(`${BASE_URL}/state`);
                
                if (!response.ok) throw new Error('Erreur réseau');
                
                const state = await response.json();
                lampeState = state.etat;
                logDebug('État lampe:', lampeState);
                
            } catch (err) {
                logDebug('Erreur état lampe:', err);
                showToast('Erreur de connexion', 'error');
            } finally {
                updateUIState();
            }
        }

        // ===== GESTION DU TEMPS =====
        async function updateClock() {
            try {
                const response = await fetch(`${BASE_URL}/time`);
                if (!response.ok) throw new Error('Erreur réseau');
                
                const time = await response.json();
                logDebug('Time response:', time);
                
                document.getElementById('heure').textContent = padZero(time.heure);
                document.getElementById('minute').textContent = padZero(time.minute);
                document.getElementById('seconde').textContent = padZero(time.seconde);
                
            } catch (err) {
                logDebug('Erreur horloge:', err);
                // Fallback à l'heure locale
                const now = new Date();
                document.getElementById('heure').textContent = padZero(now.getHours());
                document.getElementById('minute').textContent = padZero(now.getMinutes());
                document.getElementById('seconde').textContent = padZero(now.getSeconds());
            }
        }

        // ===== GESTION DES CONFIGURATIONS =====
        document.getElementById('config-form').addEventListener('submit', async (e) => {
            e.preventDefault();
            
            btnReglageEl.disabled = true;
            
            try {
                const configData = {
                    allumage: splitInputAndParseToInt(document.getElementById('on_config')),
                    extinction: splitInputAndParseToInt(document.getElementById('off_config'))
                };

                // Validation supplémentaire
                const onDate = new Date(
                    configData.allumage.annee,
                    configData.allumage.mois - 1,
                    configData.allumage.jour,
                    configData.allumage.heure,
                    configData.allumage.minute
                );
                
                const offDate = new Date(
                    configData.extinction.annee,
                    configData.extinction.mois - 1,
                    configData.extinction.jour,
                    configData.extinction.heure,
                    configData.extinction.minute
                );
                
                if (offDate <= onDate) {
                    throw new Error("L'extinction doit être après l'allumage");
                }

                logDebug('Envoi configuration:', configData);
                
                const response = await fetch(`${BASE_URL}/config`, {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/json'
                    },
                    body: JSON.stringify(configData)
                });
                
                if (!response.ok) {
                    throw new Error('Erreur lors de l\'envoi de la configuration');
                }
                
                const result = await response.json();
                logDebug('Réponse configuration:', result);
                
                showToast('Configuration enregistrée avec succès');
                
            } catch (err) {
                logDebug('Erreur configuration:', err);
                showToast(err.message, 'error');
            } finally {
                btnReglageEl.disabled = false;
            }
        });

        // ===== ÉVÉNEMENTS =====
        btnLampeEl.addEventListener('click', toggleLampe);

        // ===== INITIALISATION =====
        function init() {
            // Initialiser l'UI avec l'état "chargement"
            updateUIState();
            
            // Démarrer l'horloge
            updateClock();
            setInterval(updateClock, 1000);
            
            // Vérifier l'état de la lampe
            checkLampeState();
            setInterval(checkLampeState, 1000);
            
            // Pré-remplir les champs datetime-local avec l'heure actuelle
            const now = new Date();
            const timeString = now.toISOString().slice(0, 16);
            document.getElementById('on_config').value = timeString;
            
            // Ajouter 1 heure pour l'extinction par défaut
            now.setHours(now.getHours() + 1);
            document.getElementById('off_config').value = now.toISOString().slice(0, 16);
            
            logDebug('Application initialisée');
        }

        // Démarrer quand le DOM est prêt
        if (document.readyState !== 'loading') {
            init();
        } else {
            document.addEventListener('DOMContentLoaded', init);
        }
    </script>
</body>
</html>
)rawliteral";
