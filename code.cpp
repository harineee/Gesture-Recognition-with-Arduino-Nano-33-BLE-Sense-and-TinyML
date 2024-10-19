// Matrix size for simulation
const int MATRIX_SIZE = 2;

// Define fixed-point scale for simulation (Q15 format for fixed-point arithmetic)
const int FIXED_POINT_SCALE = 32768; // Equivalent to 2^15

// LED pins to represent pipeline stages
const int LOAD_PIN = 2;
const int MULTIPLY_PIN = 3;
const int ACCUMULATE_PIN = 4;
const int OUTPUT_PIN = 5;

// Matrices for simulation
int16_t matrixA[MATRIX_SIZE][MATRIX_SIZE] = {
  {10000, 20000},
  {30000, 40000}
};

int16_t matrixB[MATRIX_SIZE][MATRIX_SIZE] = {
  {5000, 6000},
  {7000, 8000}
};

int16_t resultMatrix[MATRIX_SIZE][MATRIX_SIZE] = {0};

void setup() {
  // Initialize LED pins as outputs
  pinMode(LOAD_PIN, OUTPUT);
  pinMode(MULTIPLY_PIN, OUTPUT);
  pinMode(ACCUMULATE_PIN, OUTPUT);
  pinMode(OUTPUT_PIN, OUTPUT);

  // Start the matrix multiplication simulation
  Serial.begin(9600);
  simulateMatrixMultiplication();
}

void loop() {
  // Nothing in loop since matrix multiplication is simulated in setup
}

// Function to simulate matrix multiplication with pipelining and fixed-point arithmetic
void simulateMatrixMultiplication() {
  // Matrix multiplication using fixed-point arithmetic
  for (int i = 0; i < MATRIX_SIZE; i++) {
    for (int j = 0; j < MATRIX_SIZE; j++) {
      resultMatrix[i][j] = 0;

      for (int k = 0; k < MATRIX_SIZE; k++) {
        // Stage 1: Load matrix values (simulated by turning on LOAD_PIN)
        digitalWrite(LOAD_PIN, HIGH);
        delay(500);  // Simulate delay for loading data
        digitalWrite(LOAD_PIN, LOW);

        // Stage 2: Multiply (fixed-point multiplication)
        digitalWrite(MULTIPLY_PIN, HIGH);
        int32_t product = ((int32_t)matrixA[i][k] * (int32_t)matrixB[k][j]) / FIXED_POINT_SCALE;
        delay(500);  // Simulate delay for multiplication
        digitalWrite(MULTIPLY_PIN, LOW);

        // Stage 3: Accumulate results (matrix addition)
        digitalWrite(ACCUMULATE_PIN, HIGH);
        resultMatrix[i][j] += product;
        delay(500);  // Simulate delay for accumulation
        digitalWrite(ACCUMULATE_PIN, LOW);
      }

      // Stage 4: Output result
      digitalWrite(OUTPUT_PIN, HIGH);
      Serial.print("Result[");
      Serial.print(i);
      Serial.print("][");
      Serial.print(j);
      Serial.print("]: ");
      Serial.println(resultMatrix[i][j]);  // Print the result in fixed-point format
      delay(500);  // Simulate delay for output
      digitalWrite(OUTPUT_PIN, LOW);
    }
  }
}
