# Softwareentwicklungspraktikum

Moin zusammen hier ein paar Informationen:

Bin mit dem Frontend fast durch was noch fehlt sind der grafische Export die drei Checkboxen wegen Visibility, sowie noch Drag and Drop und gegebenenfalls raus und reinzoomen.
Ebenfalls noch ein paar technisch relevante Fragen z.B. sollte der User nicht zwei Knoten and der Selben Stelle erstellen dürfen und Feedback wann ein System singulär oder überbestimmt ist.
Man kann aber schon vernünftig Tragwerke eingeben sowie steht das Verbindung zum Backend. Dieses benutzt eigene Datentypen damit es modular ist. Die run-Funktion nimmt Lager, Kräfte, Stäbe, E, A, und 
linear(ob linear oder nichtLinear simuliert werden soll) als Input und gibt die verschobenen Stäbe zurück. Die Inputs sind noch als std::vector die assemblierte Matrix würde ich aber mit 
la::Matrix (ist das la file aus cppNum, also mit der Eigen Bibliothek) machen weil wir dann schon direkt einen Solver dabei haben. 

Anleitung zum compileren: 
Zuerst muss das Backend zu einer static library compiliert werden. Dafür in Tragwerk/Backend/ "cmake -S . -B ../bin" und dann natürlich in Tragwerk/bin make ausführen.
Nun führen wir in Tragwerk/  "cmake -S . -B build" aus und machen make in Tragwerk/build , und erhalten damit die fertige Ausführbare
