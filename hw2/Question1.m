% 參數設置
N = 500; % 位數
freqOffset = 3; % 頻率偏移
sampleRate = 1e6; % 取樣率
t = (0:N-1)/sampleRate; % 時間序列

% 生成隨機位序列
data = randi([0 1], 1, N); % 隨機位序列

% 將位序列對映到QPSK符號
dataSymbolsIn = bi2de(reshape(data, 2, []).', 'left-msb'); % .'是轉置運算子，用於將矩陣的行列互換
qpskSymbols = exp(1j*pi/4*(2*dataSymbolsIn + 1));

% 定義不同的 SNR 值
SNR_dB_values = [0, 10, 20];

for i = 1:length(SNR_dB_values)
    % 當前 SNR 值
    SNR_dB = SNR_dB_values(i);
    
    % 添加高斯白雜訊和頻率偏移
    snrLinear = 10^(SNR_dB/10); % 從對數單位(dB)轉換為線性單位
    noiseVariance = 1/(2*snrLinear); % 根據 SNR 計算雜訊變異數
    noise = sqrt(noiseVariance) * (randn(size(qpskSymbols)) + 1j*randn(size(qpskSymbols))); % 雜訊包含實部、虛部
    
    receivedSymbols = qpskSymbols + noise; %將生成的雜訊加到原始的QPSK符號
    
    % 繪製 QPSK 星座圖
    figure;
    plot(real(receivedSymbols), imag(receivedSymbols), 'rx'); % rx是LineSpec，r表示用紅色繪製，x表示用x標記每個點
    title(['QPSK Constellation Diagram (SNR = ' num2str(SNR_dB) ' dB)']);
    xlabel('Real Part');
    ylabel('Imaginary Part');
    grid on; % 開啟格線
end
