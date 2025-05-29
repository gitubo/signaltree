# Cerca tutti i file .cpp nella cartella examples/
file(GLOB EXAMPLE_SOURCES "*.cpp")

foreach(example_source ${EXAMPLE_SOURCES})
    # Ottieni il nome del file senza estensione
    get_filename_component(example_name ${example_source} NAME_WE)

    # Crea un eseguibile per ciascun file .cpp
    add_executable(${example_name} ${example_source})

    # Collega la libreria principale (signaltree)
    target_link_libraries(${example_name} PRIVATE signaltree)

    # Includi le directory necessarie
    target_include_directories(${example_name} PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${LUAJIT_INCLUDE_DIRS}
    )

    # Collega LuaJIT se necessario
    target_link_libraries(${example_name} PRIVATE ${LUAJIT_LIBRARIES})

    # Aggiungi eventualmente i test
    add_test(NAME ${example_name} COMMAND ${example_name})
endforeach()
