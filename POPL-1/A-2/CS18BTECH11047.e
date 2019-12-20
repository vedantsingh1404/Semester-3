note
    date        : "19/11/2019"
    description : "merge sort"

class
    CS18BTECH11047

inherit
    ARGUMENTS

create
    make

feature
        --variables initialisation
    num_elem: INTEGER
    input_elements: ARRAY[INTEGER]
    h: MINHEAP
    sorted: ARRAY[INTEGER]
    i_f: PLAIN_TEXT_FILE
    o_f: PLAIN_TEXT_FILE

feature {NONE}

    make
        local
            i: INTEGER
        do
            create i_f.make_open_read("input.txt")
            create o_f.make_open_write("output.txt")

            input
            sorted := heapsort(num_elem, input_elements)
            print_array(sorted)

            i_f.close
            o_f.close
        end

    input
            --takes input
        local
            i: INTEGER

        do
            i_f.read_word
            num_elem := i_f.last_string.to_integer
            create input_elements.make(1, num_elem)

            from
                i := 1
            invariant
                range : i > 0 and i <= num_elem + 1
            until
                i > num_elem
            loop
                i_f.read_word
                input_elements[i] := i_f.last_string.to_integer
                i := i + 1
            end

            ensure
                non_zero : num_elem > 0
            rescue
                o_f.put_string("INVALID")
                o_f.close
        end

    heapsort(x: INTEGER y: ARRAY[INTEGER]): ARRAY[INTEGER]
            --returns sorted form of array
        require
            not_empty : x > 0
        local
            i: INTEGER
            t: INTEGER
        do
            create h.make(x, y)
            h.build_heap
            create Result.make(1,h.size)
            t := h.size
            from
                i := 1
            invariant
                range : i > 0 and i <= t + 1
            until
                i > t
            loop
                Result[i] := h.peek
                h.delete_min
                i := i + 1
            end

            ensure
                sorted : check_sorted(Result) = 1
                not_changed : y = old y
            rescue
                o_f.put_string("INVALID")
                o_f.close
        end

    check_sorted(x: ARRAY[INTEGER]): INTEGER
            --checks if the final array is sorted
        require
            not_empty : x.count > 0
        local
            i: INTEGER
        do
            Result := 1
            from
                i := 1
            invariant
                range : i > 0 and i <= x.count
            until
                i > x.count - 1
            loop
                if x[i] > x[i + 1] then
                    Result := 1
                end
                i := i + 1
            end
            ensure
                x_not_changed : x = old x
            rescue
                o_f.put_string("INVALID")
                o_f.close
        end

    print_array(x: ARRAY[INTEGER])
            --prints the given array according to the output format
        local
            i: INTEGER
        do
            from
                i := 1
            invariant
                range : i > 0 and i <= x.count + 1
            until
                i > x.count
            loop
                o_f.put_integer(x[i])
                o_f.put_string(" ")
                -- print(x[i])
                -- print(" ")
                i := i + 1
            end
        end
end
