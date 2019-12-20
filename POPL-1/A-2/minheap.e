class
    MINHEAP

create
    make

feature
        --variable initialisation
    heap: ARRAY[INTEGER]
    n: INTEGER
    size: INTEGER

feature
        --main heap functions

    make(x: INTEGER y: ARRAY[INTEGER])
        require
            x_non_zero : x > 0
            y_not_empty : y /= Void
            size_check : y.count = x
        local
            i: INTEGER
        do
            n := x
            size := x
            create heap.make(1, n)
            from
                i := 1
            invariant
                range : i > 0 and i <= n + 1
            until
                i > n
            loop
                heap[i] := y[i]
                i := i + 1
            end
        end

    give_size: INTEGER
            --returns the size of the heap
        do
            Result := size
        end

    peek: INTEGER
            --return the min element of the heap
        require
            not_empty : size > 0
        do
            Result := heap[1]
        end


    check_heap(i: INTEGER): BOOLEAN
            --checks whether below trees are heaps
        local
            l: INTEGER
            r: INTEGER
        do
            Result := true
            if i > size // 2 then
                Result := true
            else
                l := 2 * i
                r := 2 * i + 1

                if 2 * i <= size and heap[l] < heap[i] then
                    Result := false
                else
                    Result := Result and check_heap(l)
                end

                if 2 * i + 1 <= size and heap[r] < heap[i] then
                    Result := false
                else
                    Result := Result and check_heap(r)
                end
            end

        end

    heapify(index: INTEGER)
            --basic heapify function
        require
            not_empty : size > 0
            bounds : index <= size and index > 0
            subtree_heap : check_heap(2 * index) and check_heap(2 * index + 1)

        local
            temp: INTEGER
            left_i: INTEGER
            right_i: INTEGER
            min_i: INTEGER
        do
            left_i := 2 * index
            right_i := 2 * index + 1

            if left_i > size then
                left_i := index
            end

            if right_i > size then
                right_i := left_i
            end

            if heap[left_i] < heap[right_i] then
                min_i := left_i
            else
                min_i := right_i
            end

            if heap[index] > heap[min_i] then
                temp := heap[index]
                heap[index] := heap[min_i]
                heap[min_i] := temp

                heapify(min_i)
            end
        end

    build_heap
            --builds the heap
        require
            not_empty : size > 0

        local
            i: INTEGER
        do
            from
                i := size // 2
            invariant
                range : i >= 0 and i <= size // 2
            until
                i < 1
            loop
                heapify(i)
                i := i - 1
            end

            ensure
                heap_built : check_heap(1) = true

        end

    delete_min
            --deletes the min element from the heap
        require
            not_empty : size > 0
        local
            temp: INTEGER
        do
            temp := heap[1]
            heap[1] := heap[size]
            heap[size] := temp

            size := size - 1

            if size > 0 then
                heapify(1)
            end
        end

    insert(x: INTEGER)
            --inserts a new element in the array
        require
            free_space : size < n
        local
            parent_i: INTEGER
            i: INTEGER
            temp: INTEGER
        do
            size := size + 1
            heap[size] := x

            i := size

            from
                parent_i := size // 2
            invariant
                range : parent_i <= n and parent_i >= 0
            until
                parent_i < 1
            loop
                if heap[i] < heap[parent_i] then
                    temp := heap[i]
                    heap[i] := heap[parent_i]
                    heap[parent_i] := temp
                end
                i := parent_i
                parent_i := parent_i // 2
            end
        end

    invariant
        n_not_zero : n > 0
        size_never_negative : size >= 0

end
