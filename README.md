# PAO1
31 agosto
versione definitiva per la seconda consegna
- separazione tra modello logico e gui
- aggiunto visitor_grafico per la creazione del widget grafico corretto : deprecata funzione setup_box_grafo
- spostata la gestione delle icone alla GUI : eliminato campo dati icona dalla classe sensore
- deprecata sensorToWI : spostata la gestione direttamente alla GUI
- visitor_dati: chiamato dalla chartBox per generare dati e costruire grafico -> eliminato dynamic_cast da on_crea_grafico_clicked
- separate implementazioni classi in diverse coppie h/cpp
- stili grafici
- aggiorna relazione e modifica grafico
- pulizia codice e inclusioni

non aggiunti: funzionalità aggiuntive
- gestione stanze
- esportazione dati
- simulazione sensori difettosi

test
test2
test 3
test 4
test 5
