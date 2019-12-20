note
    description : "chinese remainder calculator"
    date        : "15/11/2019"

class
    CS18BTECH11047

inherit
    ARGUMENTS

create
    make

feature
        --variables declaration
    num: INTEGER
    n: ARRAY[INTEGER]
    a: ARRAY[INTEGER]
    inv: ARRAY[INTEGER]
    p: ARRAY[INTEGER]
    input_file: PLAIN_TEXT_FILE
    output_file: PLAIN_TEXT_FILE

feature {NONE} -- Initialization

    make
            -- Run application.
        do
            create output_file.make_open_write ("output.txt")

            input
            construct_p(product)
            construct_inv
            output_file.put_integer(chinese_mod)
            input_file.close
            output_file.close
        end


    input
            --takes the input
        local
            i: INTEGER
        do
            create input_file.make_open_read ("input.txt")
            input_file.read_word
            num := input_file.last_string.to_integer

            create n.make(1, num)
            create a.make(1, num)

            from
                i := 1
            invariant
                range : i > 0 and i <= num + 1
            until
                i > num
            loop
                input_file.read_word
                n[i] := input_file.last_string.to_integer
                input_file.read_word
                a[i] := input_file.last_string.to_integer
                i := i + 1
            end

            ensure
                non_zero_elements : num > 0
                condition : check_co_prime = 0 and check_rest = 0
            rescue
                output_file.put_string("INVALID")
                output_file.close
        end

    product: INTEGER
            -- gives the product of all the numbers
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
        local
            i: INTEGER
        do
            Result := 1
            from
                i := 1
            invariant
                range : i > 0 and i <= num  + 1
            until
                i > num
            loop
                Result := Result * n[i]
                i := i + 1
            end
        end

  gcd (x: INTEGER y: INTEGER): INTEGER
	     do
			     if y = 0 then
				        Result := x
			     else
				        Result := gcd (y, x \\ y);
			     end
		  end

	check_co_prime: INTEGER
	        --checks whether all the the n's are co-prime
        require
            non_zero_elements: num > 0
        local
            i: INTEGER
            j: INTEGER
        do
            Result := 0
            from
                i := 1
            invariant
                i_range : i > 0 and i <= num + 1
            until
                i > num
            loop
                from
                    j := i + 1
                invariant
                    j_range : j > 0 and j <= num + 1
                until
                    j > num
                loop
                    if gcd(n[i], n[j]) > 1 then
                        Result := 1
                        j := num
                        i := num
                    end
                    j := j + 1
                end
                i := i + 1
            end

            ensure
                not_changed : n = old n
            rescue
                output_file.put_string("INVALID")
                output_file.close
        end

    check_rest: INTEGER
            --check all rest condiditons
        require
            non_zero_elements: num > 0
        local
            i: INTEGER
        do
            Result := 0
            from
                i := 1
            invariant
                range : i > 0 and i <= num + 1
            until
                i > num
            loop
                if n[i] <= a[i] then
                    Result := 1
                    i := num
                elseif n[i] <= 0 then
                    Result := 1
                    i := num
                elseif a[i] < 0 then
                    Result := 1
                    i := num
                end
                i := i + 1
            end
        end


    construct_p(x: INTEGER)
            --make the array p which contains the values when product is divided by the respective numbers
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
        local
            i: INTEGER
        do
            create p.make(1, num)
            from
                i := 1
            invariant
                range: i > 0 and i <= num + 1
            until
                i > num
            loop
                p[i] := x // n[i]
                i := i + 1
            end

            ensure
                n_not_changed : n = old n
                p_not_empty : p /= Void
            rescue
                output_file.put_string("INVALID")
                output_file.close
        end

    inv_modulo(x: INTEGER y: INTEGER): INTEGER
            --calculates the inverse modulo
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
            co_prime : gcd(x, y) = 1
        local
            i: INTEGER
        do
            from
                i := 1
            invariant
                range : i > 0 and i <= y
            until
                i > y - 1
            loop
                if (x * i) \\ y = 1 then
                    Result := i
                    i := y - 1
                end
                i := i + 1
            end
        end

    construct_inv
            -- constructing inverse modulo array
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
        local
            i: INTEGER
        do
            create inv.make(1, num)
            from
                i := 1
            invariant
                range : i > 0 and i <= num + 1
            until
                i > num
            loop
                inv[i] := inv_modulo(p[i], n[i])
                i := i + 1
            end

            ensure
                p_n_not_changes: p = old p and n = old n
                inv_not_empty: inv /= Void
            rescue
                output_file.put_string("INVALID")
                output_file.close
        end

    chinese_mod: INTEGER
            --calculates the chinese remainder
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
        local
            i: INTEGER
        do
            Result := 0
            from
                i := 1
            invariant
                range : i > 0 and i <= num + 1
            until
                i > num
            loop
                Result := Result + (inv[i] * a[i] * p[i])
                i := i + 1
            end

            Result := Result \\ product

            ensure
                chinese_correct : chinese_check(Result) = 0
                min_check : min_mod_check(Result) = 0
            rescue
                output_file.put_string("INVALID")
                output_file.close
        end


    chinese_check(x: INTEGER): INTEGER
            --checks if the calculated chinese remainder gives the given remainder with each number
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
        local
            i: INTEGER
        do
            Result := 0
            from
                i := 1
            invariant
                range : i > 0 and i <= num + 1
            until
                i > num
            loop
                if x \\ n[i] /= a[i] then
                    Result := 1
                end
                i := i + 1
            end
        end

    min_mod_check(x: INTEGER): INTEGER
            --checks if the calculated remainder is indeed the minimum
        require
            non_zero_elements : num > 0
            condition : check_co_prime = 0 and check_rest = 0
            satisfy : chinese_check(x) = 0
        local
            i: INTEGER
        do
            Result := 0
            from
                i := 1
            invariant
                range : i > 0 and i <= x
            until
                i > x - 1
            loop
                if chinese_check(i) = 0 then
                    Result := 1
                end
                i := i + 1
            end
        end
end
