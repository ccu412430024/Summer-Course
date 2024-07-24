% 讀取CSV檔案
data = readtable('movie_box_office.csv');

% 讀取每行資料
movies = data.Movie;
boxOffice = data.BoxOffice;
ratings = data.Rating;

% 繪製柱狀圖
figure;
subplot(3,1,1); % 此圖位在上1/3
bar(boxOffice);
set(gca, 'xticklabel', movies); % x軸刻度標籤
xlabel('Movies');
ylabel('Box Office(Million USD)');
title('Box Office Revenue');
grid on;

% 繪製折線圖
subplot(3,1,2); % 此圖位在中1/3
plot(ratings, '-o'); % -代表實線，o代表以圓圈標記
set(gca, 'xticklabel', movies);
xlabel('Movies');
ylabel('Ratings');
title('Movie Ratings');
grid on;

% 繪製散點圖
subplot(3,1,3); % 此圖位在下1/3
scatter(boxOffice, ratings, 'filled');
text(boxOffice+3, ratings, movies); % 文字標籤
xlabel('Box Office(Million USD)');
ylabel('Ratings');
title('Box Office Revenue vs. Ratings');
grid on;
