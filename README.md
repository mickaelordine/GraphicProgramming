# Engine

GRAPHIC PROGRAMMING ENGINE

esercizio svolto per la materia di graphic programming del corso di laurea in Informatica dell'Università di Verona.

il progetto è stato pensato per essere sviluppato seguendo due tutorial principali, uno quello di rasterTek per la parte di rendering con directX e l'altro e quello di Madhav, che spiega nel suo libro GameProgrammingC++ come strutturare l'architettura all'interno di un Engine.

NOTES:
1. il progetto usa la scheda grafica di default che viene utilizzata dal computer, se si vuole utilizzare la scheda video dedicata allora bisogna selezionarla tramite il pannello di Nvidia.
2. ricordarsi di caricare la cartella External che permette al progetto di utilizzare le librerie di SDL3 per x64, prima erano solo x86

TODO:
a. il gioco più o meno funziona, prossima cosa da fare è creare un model Class per i rettangoli e vedere come inserire la sfera come texture, magari usando un alpha blending.
b. sarebbe anche una buona idea dopo aver creato quello rettangolare per i brick, vedere se avvicinare la camera allo schermo e vedere come migliorarlo.
c. creare il power up dei proiettili (?)
d. creare una condizione di vittoria 