# PAO1
20 agosto
prima versione (in teoria) senza separazione tra modello logico e GUI
- aggiunto visitor_grafico per la creazione del widget grafico corretto : deprecata funzione setup_box_grafo
- spostata la gestione delle icone alla GUI : eliminato campo dati icona dalla classe sensore
- deprecata sensorToWI : spostata la gestione direttamente alla GUI
- sono ancora presenti qDebug, commenti e da riordinare il codice

ramo2:
- divise gerarchie in singole coppie h/cpp
- parziale pulizia codice e inclusioni ma non completa

non aggiunti
- visitor 2 per generare dati
- verifica se è necessario usare dynamic cast in on_crea_grafico_clicked
- observer per modificare min/max/soglia sensore per modificare chartbox
- aggiorna relazione e modifica grafico
- pulizia codice e inclusioni
