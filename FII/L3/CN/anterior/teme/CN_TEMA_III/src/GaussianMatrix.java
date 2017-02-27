class GaussianMatrix {

    private int countRotations; //pivotari
    private int N = 0;
    private double[][] A, extendedA, inverse;

    public GaussianMatrix(int n) {
        N = n;
        A = Util.matrixRandom(n);

        Util.displayMatrix(A, "Matricea Initiala");

        extendedA = new double[n][n * 2];

        double[][] tempIdentity = Util.matrixUnity(n);

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                extendedA[i][j] = A[i][j];
                extendedA[i][j + n] = tempIdentity[i][j];
            }
        }
    }

    public void gaussianElimination() {
        int l = 0;
        countRotations = 0;

        while ((l < N - 1)&&(A[l][l] > Util.e)) {
            pivotare_partiala(l);

            for (int i = l + 1; i < N; i++) {

                double f = -(extendedA[i][l] / extendedA[l][l]);

                for (int j = l + 1; j < 2 * N; j++) {

                    extendedA[i][j] = extendedA[i][j] + f * extendedA[l][j];
                }
                extendedA[i][l] = 0;
            }
            ++l;
        }

        if (A[l][l] <= Util.e) {
            Util.displayMatrix(A, "Matrice singulara");
            throw new Error("Matricea A este singulara");
        }

        Util.displayMatrix(extendedA, "Matricea Gaussiana Superior triunghiulara");
        doNonSingularMatrixOperations();
    }

    private void doNonSingularMatrixOperations() {
        System.out.println("\nDeterminant: " + getDeterminant() + '\n');

        calculateInverse();
        Util.displayMatrix(inverse, "Inverse");

        Util.displayMatrix(Jama.Matrix.constructWithCopy(A).inverse().getArray(), "Jama Inverse");

        System.out.println("Validation: ||A * A^-1||");
        double[][] multiplied = Util.mul(A, inverse);

        Util.displayMatrix(multiplied, "Multiplied");

        System.out.println("Validation: ||A * A^-1 - In||");
        double[][] result = Util.subtract(multiplied, Util.matrixUnity(A.length));

        Util.displayMatrix(result, "result");

        System.out.println("\n\n Norma: " + String.format("%.15f", calculateNorma(result)));

    }

    private double calculateNorma(double[][] result) {
        double maxVal = 0;
        double tempVal;

        for (int i = 0; i < N; i++) {
            tempVal = 0;
            for (int j = 0; j < N; j++) {
                tempVal += Math.abs(result[i][j]);
            }
            if(maxVal < tempVal)
            {
                maxVal = tempVal;
            }
        }
        return maxVal;
    }

    private void pivotare_partiala(int l) {
        int i = l;

        for (int j = i; j < A.length; j++) {
            if (Math.abs(extendedA[j][l]) > Math.abs(extendedA[i][l]))
                i = j;
        }

        if (i != l) {
            countRotations++;
            double[] temp = extendedA[l];
            extendedA[l] = extendedA[i];
            extendedA[i] = temp;
        }
    }

    public double getDeterminant() {
        double det = 1;

        for (int i = 0; i < N; i++)
            det *= extendedA[i][i];

        return (countRotations % 2 == 0) ? det : det * -1;
    }

    private void calculateInverse() {

        inverse = new double[N][N];
        double[] tempX = new double[N];
        for (int xi = 0; xi < N; xi++) {

            for (int i = N - 1; i >= 0; i--) {

                double sumaNecunoscuteAflate = 0;

                for (int j = i + 1; j < N; j++) {

                    sumaNecunoscuteAflate += extendedA[i][j] * tempX[j];
                }
                if(extendedA[i][i] == 0) {
                    inverse[i][xi] = 0;
                    tempX[i] = 0;
                }
                else {
                    double x = (extendedA[i][xi + N] - sumaNecunoscuteAflate) / extendedA[i][i];
                    inverse[i][xi] = x;
                    tempX[i] = x;
                }
            }
        }
    }
}