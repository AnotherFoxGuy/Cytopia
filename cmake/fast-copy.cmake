function(fast_copy FROM_DIR TO_DIR)
    file(GLOB_RECURSE files "${FROM_DIR}/*")
    get_filename_component(FROM_DIR_NAME ${FROM_DIR} NAME)

    foreach (file IN LISTS files)
        file(RELATIVE_PATH output_file ${FROM_DIR} ${file})
        set(dest "${TO_DIR}/${output_file}")
        
        add_custom_command(
                COMMENT "Copying ${output_file}"
                OUTPUT ${dest}
                DEPENDS ${file}
                COMMAND ${CMAKE_COMMAND} -E copy ${file} ${dest}
        )
        list(APPEND ALL_FILES ${dest})
    endforeach ()

    add_custom_target(
            fast_copy_${FROM_DIR_NAME} ALL
            DEPENDS ${ALL_FILES}
    )
endfunction()