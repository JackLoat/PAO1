# PAO1
20 agosto
prima versione (in teoria) senza separazione tra modello logico e GUI
- aggiunto visitor_grafico per la creazione del widget grafico corretto : deprecata funzione setup_box_grafo
- spostata la gestione delle icone alla GUI : eliminato campo dati icona dalla classe sensore
- deprecata sensorToWI : spostata la gestione direttamente alla GUI
- sono ancora presenti qDebug, commenti e da riordinare il codice

non aggiunti
- visitor 2 per generare dati
- verifica se è necessario usare dynamic cast in on_crea_grafico_clicked
- observer per modificare min/max/soglia sensore per modificare chartbox
- separare implementazioni di ogni singola classe delle gerarchie in coppie h/cpp
- aggiorna relazione e modifica grafico
- pulizia codice e inclusioni
