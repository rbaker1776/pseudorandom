function generator()
    BITSTRING_SIZE = 16000000;
    outfile = fopen("randomness.txt", "w");

    for i = 1:BITSTRING_SIZE/8
        r = randi(intmax("uint32"));
        bytes = typecast(r, 'uint8');
        fwrite(outfile, bytes, 'uint8');
    end

    flose(outfile);
end