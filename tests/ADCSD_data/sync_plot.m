%% Set up the Import Options and import the data
opts = delimitedTextImportOptions("NumVariables", 1);

% Specify range and delimiter
opts.DataLines = [1, Inf];
opts.Delimiter = ",";

% Specify column names and types
opts.VariableNames = "VarName1";
opts.VariableTypes = "double";

% Specify file level properties
opts.ExtraColumnsRule = "ignore";
opts.EmptyLineRule = "read";

% Import the data
data = readtable("D:\workspace\perdolinque\IrisUNO-VG015\tests\ADCSD_data\data.csv", opts);

%% Convert to output type
data = table2array(data);

%% Clear temporary variables
clear opts

signal = data;

% Вектор с отсчетами АЦП (12-битный, сырые коды от 0 до 4095)
% signal = ...; % Ваш вектор здесь, столбец с оцифрованными значениями (адаптируйте под реальные данные)

% Параметры
Vpp = 3; % Пиковое значение пилы в В (для справки, не используется здесь)
fs = 1000; % Частота дискретизации, Гц (замените на реальную, если известна)
dt = 1/fs;
t = (0:length(signal)-1)' * dt; % Временная шкала

% Шаг 4: Найдем diff сигнала (сначала, для шага 1-3)
diff_signal = diff(signal);

% Шаг 1: Сортируем diff по возрастанию и выкидываем 20 самых больших значений
sorted_diff = sort(abs(diff_signal));
remaining_diff = sorted_diff(1:end-20); % Удаляем 20 max (самые положительные)

% Шаг 2: Получаем среднее значение для оставшегося diff
mean_remaining = max(abs(remaining_diff));

% Шаг 3: Порог равен минус двум средним значениям
threshold = -2 * mean_remaining;

% Шаг 4: Уже посчитан diff_signal выше

% Шаг 5: Берем индексы всех значений результата diff где оно ниже порога
drop_indices = find(diff_signal < threshold);

% Шаг 6: Обработка групп consecutive индексов (сбросов)
% Находим группы consecutive drop_indices
if isempty(drop_indices)
    error('Не найдено ни одного сброса (drop). Проверьте threshold или данные.');
end

groups = {}; % Cell array для групп
current_group = [drop_indices(1)];
for i = 2:length(drop_indices)
    if drop_indices(i) == current_group(end) + 1
        current_group = [current_group; drop_indices(i)];
    else
        groups{end+1} = current_group;
        current_group = [drop_indices(i)];
    end
end
groups{end+1} = current_group; % Последняя группа

% Для каждой группы определяем конец периода и начало следующего
period_ends = []; % Индексы концов периодов
period_starts = [1]; % Начало первого периода всегда 1
for g = 1:length(groups)
    group = groups{g};
    if length(group) > 2
        warning('Группа сбросов длиной >2: %d. Берем первый как конец, последний+1 как начало.', length(group));
    end
    end_idx = group(1); % Первый в группе - конец периода
    start_idx = group(end) + 1; % Последний +1 - начало следующего
    period_ends = [period_ends; end_idx];
    period_starts = [period_starts; start_idx];
end

% Добавляем конец сигнала как условный конец последнего периода
if period_ends(end) < length(signal)
    period_ends = [period_ends; length(signal)];
end

% Удаляем дубликаты, если есть (на случай пересечений)
period_starts = unique(period_starts);
period_ends = unique(period_ends);

% Убеждаемся, что starts и ends синхронизированы (длина совпадает)
num_periods = length(period_starts);
if length(period_ends) ~= num_periods
    % Подгоняем: если ends меньше, добавляем length(signal)
    while length(period_ends) < num_periods
        period_ends = [period_ends; length(signal)];
    end
    % Если больше, обрезаем
    period_ends = period_ends(1:num_periods);
end

% Шаг 7: Считаем длину периода в отсчетах
period_lengths = period_ends - period_starts + 1; % Длина = end - start +1
max_len = max(period_lengths);
full_periods = find(period_lengths >= 0.9 * max_len); % Полные: >=90% от max
incomplete_periods = setdiff(1:num_periods, full_periods); % Остальные - неполные

num_full = length(full_periods);
num_incomplete = length(incomplete_periods);
avg_len = mean(period_lengths(full_periods)); % Средняя длина полных

% Шаг 8: Вывод информации
fprintf('Число полных периодов: %d\n', num_full);
fprintf('Число неполных периодов: %d\n', num_incomplete);
fprintf('Максимальная длина периода: %d отсчетов\n', max_len);
fprintf('Средняя длина полных периодов: %.1f отсчетов\n', avg_len);
fprintf('Среднее оставшегося diff: %.2f\n', mean_remaining);
fprintf('Порог: %.2f\n', threshold);

% Таблица с периодами
fprintf('\nПериоды:\n');
fprintf('№ | Полный? | Начало (индекс) | Конец (индекс) | Длина\n');
for i = 1:num_periods
    is_full = ismember(i, full_periods);
    if is_full
        full_str = 'Да';
    else
        full_str = 'Нет';
    end
    fprintf('%d | %s | %d | %d | %d\n', i, full_str, ...
        period_starts(i), period_ends(i), period_lengths(i));
end

% График: исходный сигнал с отметками начал (синие) и концов (красные) периодов
figure;
plot(t, signal, 'k-', 'LineWidth', 0.5);
hold on;
% Отмечаем начала периодов (синие кружки)
for i = 1:num_periods
    plot(t(period_starts(i)), signal(period_starts(i)), 'bo', 'MarkerSize', 8, 'MarkerFaceColor', 'b');
end
% Отмечаем концы периодов (красные кружки)
for i = 1:num_periods
    plot(t(period_ends(i)), signal(period_ends(i)), 'ro', 'MarkerSize', 8, 'MarkerFaceColor', 'r');
end
xlabel('Время (с)');
ylabel('Код АЦП');
title('Исходный сигнал с границами периодов');
legend('Сигнал', 'Начало периода', 'Конец периода', 'Location', 'best');
grid on;
hold off;

% Дополнительно: график diff с отметкой порога
figure;
plot(1:length(diff_signal), diff_signal, 'k-', 'LineWidth', 0.5);
hold on;
yline(threshold, 'r--', 'LineWidth', 2, 'Label', sprintf('Порог = %.2f', threshold));
xlabel('Индекс');
ylabel('diff(signal)');
title('diff сигнала с порогом');
legend('diff', 'Порог', 'Location', 'best');
grid on;
hold off;

% ... (предыдущий код остается без изменений до конца шага 8 и графиков)

% Шаг 9: Наложение всех периодов (полных и неполных) и усреднение для сглаживания шумов
if num_periods == 0
    error('Нет периодов для усреднения.');
end

% Используем максимальную длину для матрицы (чтобы покрыть все)
max_period_len = max_len; % Из шага 7

% Инициализация матрицы (строки - периоды, столбцы - отсчеты до max_len)
all_periods_matrix = nan(num_periods, max_period_len);

for j = 2:num_periods
    idx = j;
    start_idx = period_starts(idx);
    end_idx = period_ends(idx);
    period_data = signal(start_idx:end_idx);
    
    is_full_j = ismember(j, full_periods);
    
    if is_full_j
        % Для полных: интерполируем к max_period_len
        if length(period_data) ~= max_period_len
            interp_t = linspace(0, 1, length(period_data));
            new_t = linspace(0, 1, max_period_len);
            period_data = interp1(interp_t, period_data, new_t, 'linear');
        end
        all_periods_matrix(j, :) = period_data';
    else
        % Для неполных: используем как есть, без растяжения (только первые length(period_data))
        all_periods_matrix(j, 1:length(period_data)) = period_data';
        % Остальное остается NaN
    end
end

% Усреднение по строкам (по периодам), nanmean игнорирует NaN
averaged_period = nanmean(all_periods_matrix, 1)';

% Удаляем trailing NaN из усредненного (если все NaN в конце)
averaged_period = averaged_period(~isnan(averaged_period));

% Вывод информации об усреднении
fprintf('\nУсредненный период:\n');
fprintf('Длина: %d отсчетов\n', length(averaged_period));
fprintf('Минимум: %.1f\n', min(averaged_period));
fprintf('Максимум: %.1f\n', max(averaged_period));

% График: наложение всех периодов + усредненный
figure;
hold on;
colors = lines(num_periods); % Цвета для каждого периода
for j = 1:num_periods
    valid_len = find(~isnan(all_periods_matrix(j, :)), 1, 'last');
    if ~isempty(valid_len)
        plot(1:valid_len, all_periods_matrix(j, 1:valid_len), '-', 'Color', colors(j,:), 'LineWidth', 0.5);
    end
end
plot(1:length(averaged_period), averaged_period, 'k-', 'LineWidth', 2, 'DisplayName', 'Усредненный');
xlabel('Отсчет в периоде');
ylabel('Код АЦП');
title('Наложение всех периодов с усреднением');
legend('Location', 'best');
grid on;
hold off;

% Дополнительно: график усредненного сигнала vs. нормализованное время (для характеристики)
norm_t = (0:length(averaged_period)-1)' / (length(averaged_period)-1); % Нормализованное время 0..1
figure;
plot(norm_t, averaged_period, 'b-', 'LineWidth', 2);
xlabel('Нормализованное время (0..1)');
ylabel('Код АЦП');
title('Усредненный период пилы');
grid on;