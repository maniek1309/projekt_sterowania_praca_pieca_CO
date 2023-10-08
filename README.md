Opis Problemu
Nasz projekt koncentruje się na stworzeniu systemu sterowania pracą pieca CO oraz ogrzewaniem domu. Głównym celem projektu jest zapewnienie bezpiecznej i efektywnej pracy pieca CO oraz zapewnienie optymalnych warunków ogrzewania w domu. System monitoruje temperaturę w piecu CO, temperaturę CO w domu oraz temperaturę boilera. Jeśli temperatura przekroczy określone progi, system podejmuje odpowiednie działania w celu utrzymania bezpiecznej pracy pieca oraz zapewnienia komfortowego ogrzewania domu.

Aktorzy
Sterowanie Piecem: Odpowiedzialne za sterowanie procesem spalania w piecu CO.
Czujnik Temperatury Pieca (tp): Monitoruje temperaturę w piecu CO w zakresie od 10°C do 120°C.
Czujnik Temperatury CO w Domu (tpCO): Monitoruje temperaturę CO w domu w zakresie od 10°C do 60°C.
Czujnik Temperatury Boilera (tpB): Monitoruje temperaturę boilera w zakresie od 10°C do 60°C.
Operator Polecenia Shutdown: Ma możliwość zatrzymania procesu sterującego w razie konieczności.
Obiekty
Pompa CO (pCO): Odpowiedzialna za sterowanie przepływem CO w systemie grzewczym. Może znajdować się w stanie "włączony" lub "wyłączony".
Pompa Boilera (pB): Odpowiedzialna za sterowanie procesem ogrzewania wody w boilera. Może znajdować się w stanie "włączony" lub "wyłączony".
Wentylator Pieca: Steruje wentylatorem w piecu CO i może znajdować się w stanie "włączony" lub "wyłączony".
Podajnik Pieca (Pp): Steruje podajnikiem paliwa w piecu CO i może znajdować się w stanie "włączony" lub "wyłączony".
Informacja o Pracy Pieca (info): Dostarcza informacje o aktualnym stanie pieca, takie jak "praca dogrzewanie", "praca nadzór", "awaria zgasło" lub "awaria za wysoka temperatura".
Algorytm
Algorytm sterowania pracą pieca, ogrzewaniem domu i ogrzewaniem boilera jest opisany w sposób następujący:

Praca Pieca
Jeśli temperatura pieca (tp) wynosi od 60°C do 70°C, piec jest włączony (W: włączony) na 10 sekund, a podajnik pieca (Pp) jest wyłączony (Pp: wyłączony). Stan informacji to "praca nadzór".
Jeśli temperatura pieca (tp) wynosi od 50°C do 60°C, piec jest włączony (W: włączony) na 10 sekund, a podajnik pieca (Pp) jest włączony (Pp: włączony) na 10 sekund. Stan informacji to "praca dogrzewanie".
Jeśli temperatura pieca (tp) spadnie poniżej 50°C, piec jest wyłączony (W: wyłączony), a podajnik pieca (Pp) jest wyłączony (Pp: wyłączony). Stan informacji to "awaria zgasło".
Jeśli temperatura pieca (tp) przekroczy 80°C, piec jest wyłączony (W: wyłączony), a podajnik pieca (Pp) jest wyłączony (Pp: wyłączony). Stan informacji to "awaria za wysoka temperatura".
Ogrzewanie Domu
Jeśli temperatura CO w domu (tpCO) wynosi od 20°C do 25°C, a informacja o pracy pieca (info) to "praca nadzór", pompa CO (pCO) jest włączona (pCO: włączony).
Jeśli temperatura CO w domu (tpCO) przekroczy 25°C, pompa CO (pCO) jest wyłączona (pCO: wyłączony).
Ogrzewanie Boilera
Jeśli temperatura boilera (tpB) wynosi od 40°C do 50°C, a informacja o pracy pieca (info) to "praca nadzór", pompa boilera (pB) jest włączona (pB: włączony).
Jeśli temperatura boilera (tpB) przekroczy 50°C, pompa boilera (pB) jest wyłączona (pB: wyłączony).
Współbieżność
System sterowania piecem oraz czujnikiem temperatury pieca CO i boilera są zaimplementowane jako 3 niezależne procesy.
Wymiana informacji między nimi odbywa się za pomocą pamięci współdzielonej (shared memory) z zabezpieczeniem przy użyciu semaforów.
Sekcje krytyczne, obejmujące dostęp do pamięci współdzielonej, są zabezpieczone semaforem binarnym w każdym z aktorów.
Zakończenie
Proces główny, który jest odpowiedzialny za sterowanie piecem, inicjalizuje pamięć współdzieloną i przed zakończeniem pracy zamyka/usuwa obiekty systemowe, takie jak shared memory i semafory.

Projekt ten jest zaprojektowany tak, aby zapewnić bezpieczną i efektywną pracę pieca CO oraz komfortowe ogrzewanie w domu, jednocześnie wykorzystując mechanizmy zabezpieczające przed współbieżnym dostępem do danych.
