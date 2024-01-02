//
// Created by artur on 02.01.2024.
//
#include "reports.hpp"

int report1() {
    std::ofstream outputFile("struct_report.txt");  // Otwarcie pliku do zapisu

    if (outputFile.is_open()) {
        generate_structure_report(f, outputFile);  // Wywołanie funkcji zapisującej do pliku
        outputFile.close();  // Zamknięcie pliku

        std::cout << "Struktura fabryki zapisana do pliku.\n";
    } else {
        std::cerr << "Błąd otwierania pliku.\n";
    }

    return 0;
}

int report2() {
    std::ofstream outputFile("sim_report.txt");  // Otwarcie pliku do zapisu

    if (outputFile.is_open()) {
        generate_simulation_turn_report(f, outputFile, 0);  // Wywołanie funkcji zapisującej do pliku
        outputFile.close();  // Zamknięcie pliku

        std::cout << "Symulacja fabryki zapisana do pliku.\n";
    } else {
        std::cerr << "Błąd otwierania pliku.\n";
    }

    return 0;
}
}