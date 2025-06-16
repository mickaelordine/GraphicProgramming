# Engine

GRAPHIC PROGRAMMING ENGINE

esercizio svolto per la materia di graphic programming del corso di laurea in Informatica dell'Università di Verona.

il progetto è stato pensato per essere sviluppato seguyendo due tutorial principali, uno quello di rasterTek per la parte di rendering con directX e l'altro e quello di Madhav, che spiega nel suo libro GameProgrammingC++ come strutturare l'architettura all'interno di un Engine.



NOTES:
1. il progetto usa la scheda grafica di default che viene utilizzata dal computer, se si vuole utilizzare la scheda video dedicata allora bisogna selezionarla tramite il pannello di Nvidia.



APPUNTI SUL PROGETTO:

a. continua sull'implementazione dell'architettura degli attori e componenti, poi in seguito organizziamo la parte di rendering wrappando le funzionalità base di DirectX tramite una classe che fa da interfaccia.
b. ho capito che il prossimo step è integrare le funzionalità di SystemClass all'interno di game e avere una singola classe responsabile di tutto il game loop di gioco, in seguito dovremmo  modificare a cascate tutte le classi di Rastertek.

CONTINUA ELIMINANDO COMPLETAMENTE SYSTEMCLASS DALLA GERARCHIA DI CLASSI IN SOSTITUZIONE DI GAME



