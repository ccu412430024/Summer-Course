% Parameter Settings
N = 500; % Number of bits
SNR_dB = 20; % SNR¡]dB¡^
freqOffset = 3; % Frequency Offset
sampleRate = 1e6; % Sample Rate
t = (0:N-1)/sampleRate; % Time Sequence

% Generate Random Bit Sequence
data = randi([0 1], 1, N); % Random Bit Sequence

% Map Bit Sequence to QPSK Symbols
dataSymbolsIn = bi2de(reshape(data, 2, []).', 'left-msb');
qpskSymbols = exp(1j*pi/4*(2*dataSymbolsIn + 1));

% Add Gaussian White Noise and Frequency Offset
snrLinear = 10^(SNR_dB/10);
noiseVariance = 1/(2*snrLinear); % Calculate Noise Variance based on SNR
noise = sqrt(noiseVariance) * (randn(size(qpskSymbols)) + 1j*randn(size(qpskSymbols)));

receivedSymbols = qpskSymbols + noise;

% Plot QPSK Constellation Diagram
figure;
plot(real(receivedSymbols), imag(receivedSymbols), 'rx');
title('QPSK Constellation Diagram');
xlabel('Real Part');
ylabel('Imaginary Part');
grid on;
