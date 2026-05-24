# Esempio di polimorfismo dinamico con SFML

Il codice in questa cartella ([`main.cpp`](./main.cpp) mostra un caso d'uso per
il polimorfismo dinamico applicato alla manipolazione di figure geometriche sul
piano.

> Nell'esempio, vengono costruiti un cerchio e un rettangolo, che vengono poi
> fatti muovere dall'angolo in alto a sinistra all'angolo in basso a destra.

> [!TIP]
> Notare come le figure vengano create sullo _heap_ e gestite con
> `unique_ptr<Shape>` in un vettore.

Il programma mostra anche la tipica struttura di un _game loop_ utilizzato per
la visualizzazione grafica di animazioni con SFML:

```c++
while (window.isOpen()) {
  // ...
}
```

il corpo del `while` gestisce un singolo _frame_ temporale.
Nel caso specifico, il _*_frame rate_ viene impostato a 60 frame al secondo
(_frames per second_, FPS), ognuno dei quali permane per circa 15 millisecondi.

All'interno del _game loop_ si evidenziano cinque fasi significative:

1. la gestione degli eventi nel cosiddetto _event loop_;
   > Nell'esempio viene gestito solo l'evento di chiusura della finestra.
2. l'evoluzione della scena;
3. > Nell'esempio il cerchio e il rettangolo vengono spostati lungo la diagonale
   > della finestra.
4. la finestra viene pulita;
5. le figure vengono disegnate sulla finestra;
6. la finestra viene visualizzata.

Il codice usa `CMake`, `ninja` e la libreria grafica `SFML`, installabili su
Ubuntu tramite il comando `sudo apt install cmake ninja libsfml-dev`.

Per compilare il codice:

```bash
cmake -S . -B build -G "Ninja Multi-Config"
```

seguito da:

```bash
cmake --build build --config Debug
```

Per eseguire il programma:

```bash
build/Debug/shapes
```
