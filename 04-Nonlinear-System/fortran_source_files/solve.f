C BACKWARD SUBSTITUTION
      
      SUBROUTINE SOLVE(N,A,IA,L,B,X)  
      DIMENSION  A(IA,N),L(N),B(N),X(N) 
      DO 3 K = 1,N-1
        DO 2 I = K+1,N      
          B(L(I)) = B(L(I)) - A(L(I),K)*B(L(K)) 
   2    CONTINUE
   3  CONTINUE    
      X(N) = B(L(N))/A(L(N),N)
      DO 5 I = N-1,1,-1     
        SUM = B(L(I))       
        DO 4 J = I+1,N      
          SUM = SUM - A(L(I),J)*X(J)  
   4    CONTINUE  
        X(I) = SUM/A(L(I),I)
   5  CONTINUE    
      RETURN      
      END 
