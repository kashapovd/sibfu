function result = task(matrix)
  s = size(matrix);
  dec = flipud(eye(s(1)));
  result = matrix - dec;
endfunction
