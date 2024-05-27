-- phpMyAdmin SQL Dump
-- version 5.2.0
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: May 26, 2024 at 08:59 PM
-- Server version: 10.4.24-MariaDB
-- PHP Version: 7.4.29

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `firma_piece_no_pdf`
--
CREATE DATABASE IF NOT EXISTS `firma_piece_no_pdf` DEFAULT CHARACTER SET utf8 COLLATE utf8_polish_ci;
USE `firma_piece_no_pdf`;

-- --------------------------------------------------------

--
-- Table structure for table `klienci`
--

CREATE TABLE `klienci` (
  `id_klienta` int(10) NOT NULL,
  `imie` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nazwisko` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nr_tel` char(9) COLLATE utf8_polish_ci NOT NULL,
  `adres` varchar(300) COLLATE utf8_polish_ci NOT NULL,
  `usuniety` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `klienci`
--

INSERT INTO `klienci` (`id_klienta`, `imie`, `nazwisko`, `nr_tel`, `adres`, `usuniety`) VALUES
(1, 'Duke', 'Nukem', '001061991', 'Przemysłowa 3, 39-100 Ropczyce', 0),
(2, 'Jerzy', 'Kiler', '017111997', 'ul. Nowoursynowska 166, 02-787 Warszawa', 0),
(3, 'Jan', 'Niezbędny', '111111111', 'Mehoffera 84, 03-118 Warszawa', 0),
(4, 'Aneta', 'Żurek', '222222222', 'Piekarska 9, 09-400 Płock', 0),
(5, 'Grzegorz ', 'Brzęczyszczykiewicz', '333333333', 'Chrząszczewek 31, 96-230 Chrząszczewek', 0),
(6, 'Gerald', 'Riviera', '444444444', 'Domowicza, 95-080 Tuszyn', 0),
(7, 'Mariola', 'Imienna', '555555555', 'al. Tadeusza Kościuszki 107, 90-928 Łódź', 0),
(8, 'Katarzyna', 'Choroba', '665776313', 'Ogrodowa 17, 91-065 Łódź', 0),
(9, 'Katarzyna', 'Synowska', '777777777', 'Grzybowska 63, 00-844 Warszawa', 0),
(10, 'Mateusz', 'Grzyb', '888888888', 'Batalionów Chłopskich 34/36, 05-250 Radzymin', 0),
(11, 'Jan', 'Kowalski', '999999999', 'Nowodworska 24, 85-870 Bydgoszcz', 0),
(12, 'Filip', 'Jarocki', '101010101', 'Kruszwicka 1, 85-213 Bydgoszcz', 0),
(13, 'Kaja', 'Misiaczek', '121212121', 'Człuchowska 1, 77-424 Zakrzewo', 0),
(14, 'Norbert', 'Zachara', '131313131', 'Jana Rocha Bauera 1, 76-200 Słupsk', 0),
(15, 'Błażej', 'Franc', '141414141', 'Reblinko 10, 76-251 Reblinko', 0),
(16, 'Tobiasz', 'Linkowski', '161616161', 'Reblinko 2c, 76-251 Reblinko', 0),
(17, 'Wiktor', 'Kardasz', '252525252', 'Wczasowa 4, 76-270 Ustka', 0),
(18, 'Wacław', 'Pokrzywa', '686868687', 'Witolda Budryka 4, 30-072 Kraków', 0),
(19, 'Adam', 'Nowakowski', '943333487', 'Wolności 26, 05-152 Truskawka', 0);

--
-- Triggers `klienci`
--
DELIMITER $$
CREATE TRIGGER `klienci_after_delete` AFTER DELETE ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Usunięto rekord z tabeli klienci");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `klienci_after_insert` AFTER INSERT ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Dopisano rekord do tabeli klienci");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `klienci_after_update` AFTER UPDATE ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Zmodyfikowano rekord z tabeli klienci");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `klienci_before_delete` BEFORE DELETE ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba usunięcia rekordu z tabeli klienci");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `klienci_before_insert` BEFORE INSERT ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba dopisania rekordu do tabeli klienci");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `klienci_before_update` BEFORE UPDATE ON `klienci` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba modyfikacji rekordu z tabeli klienci");
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `logi`
--

CREATE TABLE `logi` (
  `id` int(12) NOT NULL,
  `czas` datetime NOT NULL,
  `operacja` varchar(100) COLLATE utf8_polish_ci NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `logi`
--

INSERT INTO `logi` (`id`, `czas`, `operacja`) VALUES
(1, '2024-05-22 14:33:26', 'Próba dopisania rekordu do tabeli pracownicy'),
(2, '2024-05-22 14:33:26', 'Dopisano rekord do tabeli pracownicy'),
(3, '2024-05-22 14:34:21', 'Próba dopisania rekordu do tabeli pracownicy'),
(4, '2024-05-22 14:34:21', 'Dopisano rekord do tabeli pracownicy'),
(5, '2024-05-22 14:35:19', 'Próba dopisania rekordu do tabeli pracownicy'),
(6, '2024-05-22 14:35:19', 'Dopisano rekord do tabeli pracownicy'),
(7, '2024-05-22 14:36:16', 'Próba dopisania rekordu do tabeli pracownicy'),
(8, '2024-05-22 14:36:16', 'Dopisano rekord do tabeli pracownicy'),
(9, '2024-05-22 14:38:07', 'Próba dopisania rekordu do tabeli pracownicy'),
(10, '2024-05-22 14:38:07', 'Dopisano rekord do tabeli pracownicy'),
(11, '2024-05-22 14:40:50', 'Próba dopisania rekordu do tabeli pracownicy'),
(12, '2024-05-22 14:40:50', 'Dopisano rekord do tabeli pracownicy'),
(13, '2024-05-22 14:42:32', 'Próba dopisania rekordu do tabeli klienci'),
(14, '2024-05-22 14:42:32', 'Dopisano rekord do tabeli klienci'),
(15, '2024-05-22 14:45:59', 'Próba dopisania rekordu do tabeli klienci'),
(16, '2024-05-22 14:45:59', 'Dopisano rekord do tabeli klienci'),
(17, '2024-05-22 16:39:55', 'Próba dopisania rekordu do tabeli klienci'),
(18, '2024-05-22 16:39:55', 'Dopisano rekord do tabeli klienci'),
(19, '2024-05-22 16:40:59', 'Próba dopisania rekordu do tabeli klienci'),
(20, '2024-05-22 16:40:59', 'Dopisano rekord do tabeli klienci'),
(21, '2024-05-22 16:44:10', 'Próba dopisania rekordu do tabeli klienci'),
(22, '2024-05-22 16:44:10', 'Dopisano rekord do tabeli klienci'),
(23, '2024-05-22 16:45:56', 'Próba dopisania rekordu do tabeli klienci'),
(24, '2024-05-22 16:45:56', 'Dopisano rekord do tabeli klienci'),
(25, '2024-05-22 16:46:56', 'Próba dopisania rekordu do tabeli klienci'),
(26, '2024-05-22 16:46:56', 'Dopisano rekord do tabeli klienci'),
(27, '2024-05-22 16:48:44', 'Próba dopisania rekordu do tabeli klienci'),
(28, '2024-05-22 16:48:44', 'Dopisano rekord do tabeli klienci'),
(29, '2024-05-22 16:49:29', 'Próba dopisania rekordu do tabeli klienci'),
(30, '2024-05-22 16:49:29', 'Dopisano rekord do tabeli klienci'),
(31, '2024-05-22 16:50:26', 'Próba dopisania rekordu do tabeli klienci'),
(32, '2024-05-22 16:50:26', 'Dopisano rekord do tabeli klienci'),
(33, '2024-05-22 16:53:12', 'Próba dopisania rekordu do tabeli klienci'),
(34, '2024-05-22 16:53:12', 'Dopisano rekord do tabeli klienci'),
(35, '2024-05-22 16:54:20', 'Próba dopisania rekordu do tabeli klienci'),
(36, '2024-05-22 16:54:20', 'Dopisano rekord do tabeli klienci'),
(37, '2024-05-22 16:55:03', 'Próba dopisania rekordu do tabeli klienci'),
(38, '2024-05-22 16:55:03', 'Dopisano rekord do tabeli klienci'),
(39, '2024-05-22 16:57:55', 'Próba dopisania rekordu do tabeli klienci'),
(40, '2024-05-22 16:57:55', 'Dopisano rekord do tabeli klienci'),
(41, '2024-05-22 16:59:52', 'Próba dopisania rekordu do tabeli klienci'),
(42, '2024-05-22 16:59:52', 'Dopisano rekord do tabeli klienci'),
(43, '2024-05-22 17:00:25', 'Próba dopisania rekordu do tabeli klienci'),
(44, '2024-05-22 17:00:25', 'Dopisano rekord do tabeli klienci'),
(45, '2024-05-22 17:01:41', 'Próba dopisania rekordu do tabeli klienci'),
(46, '2024-05-22 17:01:41', 'Dopisano rekord do tabeli klienci'),
(47, '2024-05-22 17:02:27', 'Próba dopisania rekordu do tabeli klienci'),
(48, '2024-05-22 17:02:27', 'Dopisano rekord do tabeli klienci'),
(49, '2024-05-22 17:03:33', 'Próba dopisania rekordu do tabeli pracownicy'),
(50, '2024-05-22 17:03:33', 'Dopisano rekord do tabeli pracownicy'),
(51, '2024-05-22 17:04:50', 'Próba dopisania rekordu do tabeli pracownicy'),
(52, '2024-05-22 17:04:50', 'Dopisano rekord do tabeli pracownicy'),
(53, '2024-05-22 17:05:40', 'Próba dopisania rekordu do tabeli pracownicy'),
(54, '2024-05-22 17:05:40', 'Dopisano rekord do tabeli pracownicy'),
(55, '2024-05-22 17:06:31', 'Próba dopisania rekordu do tabeli pracownicy'),
(56, '2024-05-22 17:06:31', 'Dopisano rekord do tabeli pracownicy'),
(57, '2024-05-22 17:09:03', 'Próba dopisania rekordu do tabeli piece'),
(58, '2024-05-22 17:09:03', 'Dopisano rekord do tabeli piece'),
(59, '2024-05-22 17:12:14', 'Próba dopisania rekordu do tabeli piece'),
(60, '2024-05-22 17:12:14', 'Dopisano rekord do tabeli piece'),
(61, '2024-05-22 17:14:34', 'Próba dopisania rekordu do tabeli piece'),
(62, '2024-05-22 17:14:34', 'Dopisano rekord do tabeli piece'),
(63, '2024-05-22 17:16:12', 'Próba dopisania rekordu do tabeli piece'),
(64, '2024-05-22 17:16:12', 'Dopisano rekord do tabeli piece'),
(65, '2024-05-22 17:17:52', 'Próba dopisania rekordu do tabeli piece'),
(66, '2024-05-22 17:17:52', 'Dopisano rekord do tabeli piece'),
(67, '2024-05-22 17:19:34', 'Próba dopisania rekordu do tabeli piece'),
(68, '2024-05-22 17:19:34', 'Dopisano rekord do tabeli piece'),
(69, '2024-05-22 17:22:15', 'Próba dopisania rekordu do tabeli piece'),
(70, '2024-05-22 17:22:15', 'Dopisano rekord do tabeli piece'),
(71, '2024-05-22 17:23:01', 'Próba dopisania rekordu do tabeli piece'),
(72, '2024-05-22 17:23:01', 'Dopisano rekord do tabeli piece'),
(73, '2024-05-22 17:25:24', 'Próba dopisania rekordu do tabeli piece'),
(74, '2024-05-22 17:25:24', 'Dopisano rekord do tabeli piece'),
(75, '2024-05-22 17:29:03', 'Próba dopisania rekordu do tabeli zlecenia'),
(76, '2024-05-22 17:29:03', 'Dopisano rekord do tabeli zlecenia'),
(77, '2024-05-22 17:33:57', 'Próba dopisania rekordu do tabeli zlecenia'),
(78, '2024-05-22 17:33:57', 'Dopisano rekord do tabeli zlecenia'),
(79, '2024-05-22 17:36:43', 'Próba dopisania rekordu do tabeli zlecenia'),
(80, '2024-05-22 17:36:43', 'Dopisano rekord do tabeli zlecenia'),
(81, '2024-05-22 17:38:09', 'Próba dopisania rekordu do tabeli zlecenia'),
(82, '2024-05-22 17:38:09', 'Dopisano rekord do tabeli zlecenia'),
(83, '2024-05-22 17:41:30', 'Próba dopisania rekordu do tabeli zlecenia'),
(84, '2024-05-22 17:41:30', 'Dopisano rekord do tabeli zlecenia'),
(85, '2024-05-22 17:44:24', 'Próba dopisania rekordu do tabeli zlecenia'),
(86, '2024-05-22 17:44:24', 'Dopisano rekord do tabeli zlecenia'),
(87, '2024-05-22 17:46:57', 'Próba dopisania rekordu do tabeli zlecenia'),
(88, '2024-05-22 17:46:57', 'Dopisano rekord do tabeli zlecenia'),
(89, '2024-05-22 17:48:50', 'Próba dopisania rekordu do tabeli zlecenia'),
(90, '2024-05-22 17:48:50', 'Dopisano rekord do tabeli zlecenia'),
(91, '2024-05-22 17:50:22', 'Próba dopisania rekordu do tabeli zlecenia'),
(92, '2024-05-22 17:50:22', 'Dopisano rekord do tabeli zlecenia'),
(93, '2024-05-22 18:20:31', 'Próba dopisania rekordu do tabeli zlecenia'),
(94, '2024-05-22 18:20:31', 'Dopisano rekord do tabeli zlecenia'),
(95, '2024-05-22 18:24:24', 'Próba dopisania rekordu do tabeli zlecenia'),
(96, '2024-05-22 18:24:24', 'Dopisano rekord do tabeli zlecenia'),
(97, '2024-05-22 18:25:52', 'Próba dopisania rekordu do tabeli zlecenia'),
(98, '2024-05-22 18:25:52', 'Dopisano rekord do tabeli zlecenia'),
(99, '2024-05-22 18:27:31', 'Próba dopisania rekordu do tabeli zlecenia'),
(100, '2024-05-22 18:27:31', 'Dopisano rekord do tabeli zlecenia'),
(101, '2024-05-22 18:29:04', 'Próba dopisania rekordu do tabeli zlecenia'),
(102, '2024-05-22 18:29:04', 'Dopisano rekord do tabeli zlecenia'),
(103, '2024-05-22 18:31:42', 'Próba dopisania rekordu do tabeli zlecenia'),
(104, '2024-05-22 18:31:42', 'Dopisano rekord do tabeli zlecenia'),
(105, '2024-05-22 18:33:08', 'Próba dopisania rekordu do tabeli zlecenia'),
(106, '2024-05-22 18:33:08', 'Dopisano rekord do tabeli zlecenia'),
(107, '2024-05-22 18:34:39', 'Próba dopisania rekordu do tabeli zlecenia'),
(108, '2024-05-22 18:34:39', 'Dopisano rekord do tabeli zlecenia'),
(109, '2024-05-22 18:35:40', 'Próba dopisania rekordu do tabeli zlecenia'),
(110, '2024-05-22 18:35:40', 'Dopisano rekord do tabeli zlecenia'),
(111, '2024-05-22 18:52:46', 'Próba dopisania rekordu do tabeli klienci'),
(112, '2024-05-22 18:52:46', 'Dopisano rekord do tabeli klienci'),
(113, '2024-05-22 19:29:47', 'Próba dopisania rekordu do tabeli zlecenia'),
(114, '2024-05-22 19:29:47', 'Dopisano rekord do tabeli zlecenia'),
(115, '2024-05-22 19:43:35', 'Próba modyfikacji rekordu z tabeli klienci'),
(116, '2024-05-22 19:43:35', 'Zmodyfikowano rekord z tabeli klienci'),
(117, '2024-05-26 17:29:27', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(118, '2024-05-26 17:29:27', 'Zmodyfikowano rekord w tabeli zlecenia'),
(119, '2024-05-26 17:29:28', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(120, '2024-05-26 17:29:28', 'Zmodyfikowano rekord w tabeli zlecenia'),
(122, '2024-05-26 18:22:55', 'Próba dopisania rekordu do tabeli zlecenia'),
(123, '2024-05-26 18:22:55', 'Dopisano rekord do tabeli zlecenia'),
(124, '2024-05-26 18:23:05', 'Próba usunięcia rekordu z tabeli zlecenia'),
(125, '2024-05-26 18:23:05', 'Usunięto rekord z tabeli zlecenia'),
(127, '2024-05-26 18:25:00', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(128, '2024-05-26 18:25:00', 'Zmodyfikowano rekord w tabeli zlecenia'),
(129, '2024-05-26 18:25:15', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(130, '2024-05-26 18:25:15', 'Zmodyfikowano rekord w tabeli zlecenia'),
(131, '2024-05-26 18:26:21', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(132, '2024-05-26 18:26:21', 'Zmodyfikowano rekord w tabeli zlecenia'),
(134, '2024-05-26 18:26:26', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(135, '2024-05-26 18:26:26', 'Zmodyfikowano rekord w tabeli zlecenia'),
(137, '2024-05-26 18:28:09', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(138, '2024-05-26 18:28:09', 'Zmodyfikowano rekord w tabeli zlecenia'),
(140, '2024-05-26 18:28:11', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(141, '2024-05-26 18:28:11', 'Zmodyfikowano rekord w tabeli zlecenia'),
(143, '2024-05-26 18:28:11', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(144, '2024-05-26 18:28:11', 'Zmodyfikowano rekord w tabeli zlecenia'),
(146, '2024-05-26 18:28:12', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(147, '2024-05-26 18:28:12', 'Zmodyfikowano rekord w tabeli zlecenia'),
(149, '2024-05-26 18:28:12', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(150, '2024-05-26 18:28:12', 'Zmodyfikowano rekord w tabeli zlecenia'),
(152, '2024-05-26 18:28:12', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(153, '2024-05-26 18:28:12', 'Zmodyfikowano rekord w tabeli zlecenia'),
(155, '2024-05-26 18:28:13', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(156, '2024-05-26 18:28:13', 'Zmodyfikowano rekord w tabeli zlecenia'),
(158, '2024-05-26 18:32:48', 'Próba dopisania rekordu do tabeli zlecenia'),
(159, '2024-05-26 18:32:48', 'Dopisano rekord do tabeli zlecenia'),
(160, '2024-05-26 18:33:10', 'Próba usunięcia rekordu z tabeli zlecenia'),
(161, '2024-05-26 18:33:10', 'Usunięto rekord z tabeli zlecenia'),
(162, '2024-05-26 18:34:56', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(163, '2024-05-26 18:34:56', 'Zmodyfikowano rekord w tabeli zlecenia'),
(164, '2024-05-26 18:34:56', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(165, '2024-05-26 18:34:56', 'Zmodyfikowano rekord w tabeli zlecenia'),
(166, '2024-05-26 18:34:57', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(167, '2024-05-26 18:34:57', 'Zmodyfikowano rekord w tabeli zlecenia'),
(168, '2024-05-26 18:34:57', 'Próba modyfikacji rekordu w tabeli zlecenia'),
(169, '2024-05-26 18:34:57', 'Zmodyfikowano rekord w tabeli zlecenia'),
(170, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(171, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(172, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(173, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(174, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(175, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(176, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(177, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(178, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(179, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(180, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(181, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(182, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(183, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(184, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(185, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece'),
(186, '2024-05-26 20:58:57', 'Próba modyfikacji rekordu w tabeli piece'),
(187, '2024-05-26 20:58:57', 'Zmodyfikowano rekord w tabeli piece');

-- --------------------------------------------------------

--
-- Table structure for table `piece`
--

CREATE TABLE `piece` (
  `id_pieca` int(10) NOT NULL,
  `model` varchar(30) COLLATE utf8_polish_ci NOT NULL,
  `producent` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `instrukcja` mediumblob DEFAULT NULL,
  `czy_wspierany` tinyint(1) NOT NULL,
  `usuniety` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `piece`
--

INSERT INTO `piece` (`id_pieca`, `model`, `producent`, `instrukcja`, `czy_wspierany`, `usuniety`) VALUES
(1, 'ecoTEC pure VCW 226/7-2', 'Vaillant', NULL, 1, 0),
(2, 'IsoTwin Condens T 31-CS/1', 'Saunier Duval', NULL, 1, 0),
(3, 'Cerapur Smart ZSB 22-3 C', 'Junkers', NULL, 1, 0),
(4, 'CALDAIA CIAO AT 25C', 'Beretta', NULL, 1, 0),
(5, 'Condens GC9000iW', 'Bosch', NULL, 1, 0),
(6, '2-F QUADRA II', 'Beretta', NULL, 1, 0),
(7, 'SILVER PRO 35', 'Termet', NULL, 1, 0),
(8, 'SILVER PRO 25/30', 'Termet', NULL, 1, 0),
(9, 'CLAS X CF', 'ARISTON', NULL, 1, 0);

--
-- Triggers `piece`
--
DELIMITER $$
CREATE TRIGGER `piece_after_delete` AFTER DELETE ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Usunięto rekord z tabeli piece");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `piece_after_insert` AFTER INSERT ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Dopisano rekord do tabeli piece");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `piece_after_update` AFTER UPDATE ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Zmodyfikowano rekord w tabeli piece");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `piece_before_delete` BEFORE DELETE ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba usunięcia rekordu z tabeli piece");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `piece_before_insert` BEFORE INSERT ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba dopisania rekordu do tabeli piece");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `piece_before_update` BEFORE UPDATE ON `piece` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba modyfikacji rekordu w tabeli piece");
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `pracownicy`
--

CREATE TABLE `pracownicy` (
  `id_pracownika` int(6) NOT NULL,
  `imie` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `imie2` varchar(60) COLLATE utf8_polish_ci DEFAULT NULL,
  `nazwisko` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `nr_tel` char(9) COLLATE utf8_polish_ci NOT NULL,
  `stanowisko` varchar(60) COLLATE utf8_polish_ci NOT NULL,
  `login` varchar(30) COLLATE utf8_polish_ci NOT NULL,
  `haslo` varchar(10) COLLATE utf8_polish_ci NOT NULL,
  `usuniety` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `pracownicy`
--

INSERT INTO `pracownicy` (`id_pracownika`, `imie`, `imie2`, `nazwisko`, `nr_tel`, `stanowisko`, `login`, `haslo`, `usuniety`) VALUES
(1, 'Jakub', NULL, 'Celej', '664664664', 'Kierownik', 'prać1', 'test123ABC', 0),
(2, 'Magda', NULL, 'Pomocna', '934213478', 'Helpdesk', 'MagdaPom99', 'zaq1@WSX', 0),
(3, 'Mariola', 'Natalia', 'Gouda', '412359376', 'Serwisant', 'margo76', 'ser99WIS', 0),
(4, 'Adam', NULL, 'Adamczyk', '138412098', 'Serwisant', 'AdaAda', 'nowehasło', 0),
(5, 'Sebastian', NULL, 'Biurowski', '556677889', 'Helpdesk', 'sebiur', 'burek99', 0),
(6, 'Jerzy', NULL, 'Zwierzyński', '093923423', 'Serwisant', 'jeżozwierz1', 'jeżo1!', 0),
(7, 'Eryk', NULL, 'Basa', '727272727', 'Helpdesk', 'ebas23', 'a2@axF!!', 0),
(8, 'Helena', 'Anastazja', 'Kryszewska', '288228821', 'Serwisant', 'h.kryszewska', 'anaNAS32!', 0),
(9, 'Błażej', NULL, 'Stodolny', '034123999', 'Serwisant', 'stodolny5', 'Błażej12#', 0),
(10, 'Zygmnunt', NULL, 'Wodyński', '987789987', 'Helpdesk', 'z.wodyński', 'zyguś926', 0);

--
-- Triggers `pracownicy`
--
DELIMITER $$
CREATE TRIGGER `pracownicy_after_delete` AFTER DELETE ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Usunięto rekord z tabeli pracownicy");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `pracownicy_after_insert` AFTER INSERT ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Dopisano rekord do tabeli pracownicy");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `pracownicy_after_update` AFTER UPDATE ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Zmodyfikowano rekord w tabeli pracownicy");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `pracownicy_before_delete` BEFORE DELETE ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba usunięcia rekordu z tabeli pracownicy");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `pracownicy_before_insert` BEFORE INSERT ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba dopisania rekordu do tabeli pracownicy");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `pracownicy_before_update` BEFORE UPDATE ON `pracownicy` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba modyfikacji rekordu w tabeli pracownicy");
END
$$
DELIMITER ;

-- --------------------------------------------------------

--
-- Table structure for table `zlecenia`
--

CREATE TABLE `zlecenia` (
  `id_zlecenia` int(10) NOT NULL,
  `id_pracownika` int(6) NOT NULL,
  `id_pieca` int(10) NOT NULL,
  `id_klienta` int(10) NOT NULL,
  `status` varchar(20) COLLATE utf8_polish_ci NOT NULL,
  `data_zgloszenia` date DEFAULT NULL,
  `data_zakonczenia` date DEFAULT NULL,
  `opis` varchar(2000) COLLATE utf8_polish_ci NOT NULL,
  `data_serwisu` date DEFAULT NULL,
  `komentarz` varchar(2000) COLLATE utf8_polish_ci DEFAULT NULL,
  `cena_serwisu` double DEFAULT NULL,
  `czy_oplacony` tinyint(1) DEFAULT NULL,
  `usuniety` tinyint(1) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8 COLLATE=utf8_polish_ci;

--
-- Dumping data for table `zlecenia`
--

INSERT INTO `zlecenia` (`id_zlecenia`, `id_pracownika`, `id_pieca`, `id_klienta`, `status`, `data_zgloszenia`, `data_zakonczenia`, `opis`, `data_serwisu`, `komentarz`, `cena_serwisu`, `czy_oplacony`, `usuniety`) VALUES
(1, 3, 1, 1, 'Otwarte', '2024-03-12', NULL, 'Piec w nocy przestaje działać, w dzień działa bez problemu', '2024-03-15', 'Problemy z instalacją elektryczną klienta', 100, 0, 0),
(2, 4, 2, 2, 'Zamknięte', '2024-03-29', '2024-04-03', 'Piec klienta działa głośniej niż jest to oczekiwane', '2024-04-03', 'Wymieniono podzespoły pieca powodujące problem', 500, 1, 0),
(3, 6, 3, 3, 'Zamknięte', '2024-04-29', '2024-05-01', 'Piec nie dostaje zasilania', '2024-05-01', 'Piec nie był podłączony do prądu', 100, 1, 0),
(4, 9, 4, 4, 'Otwarte', '2024-05-07', '2024-05-09', 'Przycisk zwiększenia temperatury nie działa', '2024-05-09', 'Usterkę naprawiono', 150, 1, 0),
(5, 8, 5, 5, 'Otwarte', '2024-05-23', NULL, 'Piec pracuje za głośno', '2024-05-28', NULL, NULL, NULL, 0),
(6, 4, 6, 6, 'Otwarte', '2024-05-21', NULL, 'Problem z połączeniem termostatu do pieca', NULL, NULL, NULL, NULL, 0),
(7, 6, 7, 7, 'Zamknięte', '2024-04-08', '2024-04-17', 'Problem z połączeniem  między termostatem a piecem', '2024-04-17', 'Termostat posiada wadę fabryczną', 100, 1, 0),
(8, 9, 8, 8, 'Otwarte', '2024-05-15', NULL, 'Piec co kilka godzin traci zasilanie', '2024-05-21', 'Wadliwe gniazdo elektryczne', 300, 0, 0),
(9, 8, 9, 9, 'Otwarte', '2024-05-23', NULL, 'Piec traci połączenie z zasilaniem', '2024-06-03', NULL, NULL, NULL, 0),
(10, 6, 4, 10, 'Zamknięte', '2023-12-06', '2023-12-11', 'Piec nagle przestał działać', '2023-12-11', NULL, 1500, 1, 0),
(11, 9, 2, 11, 'Zamknięte', '2023-12-27', '2024-01-08', 'Połowa przycisków kontrolujących piec nie działa', '2024-01-08', 'Nastąpiło zwarcie w konsoli sterowniczej', 300, 1, 0),
(12, 4, 8, 12, 'Otwarte', '2023-11-24', '2023-12-01', 'Piec nie włącza się', NULL, 'Serwis anulowano, użytkownik rozwiązał problem', NULL, NULL, 0),
(13, 8, 8, 13, 'Otwarte', '2024-05-20', NULL, 'Przyciski na konsoli sterującej pieca nie działają poprawnie', '2024-05-27', NULL, NULL, NULL, 0),
(14, 3, 1, 14, 'Zamknięte', '2024-05-07', '2024-05-15', 'Piec nie łączy się z aplikacją', '2024-05-15', NULL, NULL, NULL, 0),
(15, 9, 6, 15, 'Zamknięte', '2024-02-06', '2024-02-15', 'Ekran konsoli sterowniczej pieca nic nie pokazuje', '2024-02-15', NULL, 350, 1, 0),
(16, 6, 7, 16, 'Zamknięte', '2024-02-28', '2024-04-08', 'Piec nie łączy się z aplikacją', '2024-04-08', NULL, 100, 1, 0),
(17, 3, 2, 17, 'Zamknięte', '2024-03-26', '2024-04-05', 'Piec przecieka', '2024-04-05', NULL, 170, 1, 0),
(18, 4, 3, 18, 'Zamknięte', '2024-04-30', '2024-05-07', 'Piec nie łączy się z aplikacją', '2024-05-07', 'Klient nie pobrał odpowiedniej aplikacji', 100, 1, 0),
(19, 4, 1, 1, 'Otwarte', '2024-05-20', NULL, 'Przycisk do zwiększania temperatury na konsoli sterowniczej przestał działać', '2024-05-29', 'Wymieniono konsolę sterowniczą pieca', 430, 0, 0);

--
-- Triggers `zlecenia`
--
DELIMITER $$
CREATE TRIGGER `zlecenia_after_delete` AFTER DELETE ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Usunięto rekord z tabeli zlecenia");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `zlecenia_after_insert` AFTER INSERT ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Dopisano rekord do tabeli zlecenia");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `zlecenia_after_update` AFTER UPDATE ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Zmodyfikowano rekord w tabeli zlecenia");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `zlecenia_before_delete` BEFORE DELETE ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba usunięcia rekordu z tabeli zlecenia");
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `zlecenia_before_insert` BEFORE INSERT ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba dopisania rekordu do tabeli zlecenia");
IF(NEW.status != "Otwarte" && NEW.status != "Zamknięte") THEN
SIGNAL SQLSTATE '45000'
SET MESSAGE_TEXT = "Pole status może mieć tylko wartość Otwarte lub Zamknięte!";
END IF;
END
$$
DELIMITER ;
DELIMITER $$
CREATE TRIGGER `zlecenia_before_update` BEFORE UPDATE ON `zlecenia` FOR EACH ROW BEGIN
INSERT INTO logi(czas, operacja) VALUES (now(), "Próba modyfikacji rekordu w tabeli zlecenia");
IF(NEW.status != "Otwarte" && NEW.status != "Zamknięte") THEN
SIGNAL SQLSTATE '45000'
SET MESSAGE_TEXT = "Pole status może mieć tylko wartość Otwarte lub Zamknięte!";
END IF;
END
$$
DELIMITER ;

--
-- Indexes for dumped tables
--

--
-- Indexes for table `klienci`
--
ALTER TABLE `klienci`
  ADD PRIMARY KEY (`id_klienta`),
  ADD KEY `idx_nazwisko` (`nazwisko`);

--
-- Indexes for table `logi`
--
ALTER TABLE `logi`
  ADD PRIMARY KEY (`id`);

--
-- Indexes for table `piece`
--
ALTER TABLE `piece`
  ADD PRIMARY KEY (`id_pieca`);

--
-- Indexes for table `pracownicy`
--
ALTER TABLE `pracownicy`
  ADD PRIMARY KEY (`id_pracownika`),
  ADD UNIQUE KEY `login` (`login`),
  ADD KEY `idx_nazwisko` (`nazwisko`),
  ADD KEY `idx_stanowisko` (`stanowisko`);

--
-- Indexes for table `zlecenia`
--
ALTER TABLE `zlecenia`
  ADD PRIMARY KEY (`id_zlecenia`),
  ADD KEY `id_pracownika` (`id_pracownika`),
  ADD KEY `id_pieca` (`id_pieca`),
  ADD KEY `id_klienta` (`id_klienta`),
  ADD KEY `idx_data_zgloszenia` (`data_zgloszenia`);

--
-- AUTO_INCREMENT for dumped tables
--

--
-- AUTO_INCREMENT for table `klienci`
--
ALTER TABLE `klienci`
  MODIFY `id_klienta` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=20;

--
-- AUTO_INCREMENT for table `logi`
--
ALTER TABLE `logi`
  MODIFY `id` int(12) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=188;

--
-- AUTO_INCREMENT for table `piece`
--
ALTER TABLE `piece`
  MODIFY `id_pieca` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=10;

--
-- AUTO_INCREMENT for table `pracownicy`
--
ALTER TABLE `pracownicy`
  MODIFY `id_pracownika` int(6) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=11;

--
-- AUTO_INCREMENT for table `zlecenia`
--
ALTER TABLE `zlecenia`
  MODIFY `id_zlecenia` int(10) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=22;

--
-- Constraints for dumped tables
--

--
-- Constraints for table `zlecenia`
--
ALTER TABLE `zlecenia`
  ADD CONSTRAINT `zlecenia_ibfk_1` FOREIGN KEY (`id_pieca`) REFERENCES `piece` (`id_pieca`),
  ADD CONSTRAINT `zlecenia_ibfk_2` FOREIGN KEY (`id_klienta`) REFERENCES `klienci` (`id_klienta`),
  ADD CONSTRAINT `zlecenia_ibfk_3` FOREIGN KEY (`id_pracownika`) REFERENCES `pracownicy` (`id_pracownika`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
