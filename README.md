Projekt na studia - aplikacja biurowa firmy (serwisu pieców gazowych). Zrobiona w C++, używa MySql C++ Connector do łączenia z bazą danych oraz QT6 do stworzenia interfejsu użytkownika.

Aby aplikacja działała poprawnie należy zmienić konfigurację w plikach:

  mysql\bin\my.ini:
  
    max_allowed_packet=512M
    
  xampp\php\php.ini:
  
    max_execution_time = 259200
    
    max_input_time = 259200
    
    memory_limit = 1000M
    
    upload_max_filesize = 750M
      
    post_max_size = 750M
    

Diagram przypadków klas do projektu:
![diagram_klas](class_diagram.png)

Diagram przypadków użycia do projektu:
![diagram_przypadków_użycia](usecase_diagram.png)

Diagramy aktywności do projektu:

- Tworzenie okna głównego i logowanie:
![diagram_aktywności_logowanie](login_diagram.png)

- Ekran zarządzania klientami:
![diagram_aktywności_klienci](customer_diagram.png)

- Ekran zarządzania piecami:
![diagram_aktywności_piece](furnace_diagram.png)

- Ekran zarządzania pracownikami:
![diagram_aktywności_pracownicy](worker_diagram.png)

- Ekran zarządzania zleceniami:
![diagram_aktywności_zlecenia](job_diagram.png)
