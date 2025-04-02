CREATE DATABASE CastifyDB;
GO
USE CastifyDB;
GO

-- Users Table (Admins & Voters)
CREATE TABLE Users (
    user_id INT IDENTITY(1,1) PRIMARY KEY,
    username NVARCHAR(50) UNIQUE NOT NULL,
    password_hash NVARCHAR(255) NOT NULL, -- Store hashed passwords
    cnic NVARCHAR(15) UNIQUE NOT NULL, -- CNIC as a unique identifier
    age INT CHECK (age >= 18) NOT NULL, -- Age must be 18+
    role NVARCHAR(10) CHECK (role IN ('admin', 'voter')) NOT NULL,
    created_at DATETIME DEFAULT GETDATE()
);
GO

-- Elections Table
CREATE TABLE Elections (
    election_id INT IDENTITY(1,1) PRIMARY KEY,
    election_name NVARCHAR(100) NOT NULL,
    start_date DATETIME NULL, -- Admin starts it manually
    duration_minutes INT NOT NULL, -- Duration in minutes
    end_date AS DATEADD(MINUTE, duration_minutes, start_date) PERSISTED, -- Auto-calculated
    status NVARCHAR(20) CHECK (status IN ('scheduled', 'ongoing', 'completed')) NOT NULL DEFAULT 'scheduled',
    created_by INT NOT NULL,
    FOREIGN KEY (created_by) REFERENCES Users(user_id) ON DELETE CASCADE
);
GO

-- Candidates Table
CREATE TABLE Candidates (
    candidate_id INT IDENTITY(1,1) PRIMARY KEY,
    user_id INT NOT NULL,  -- Candidate is also a user
    election_id INT NOT NULL,
    party_name NVARCHAR(50) NOT NULL,
    FOREIGN KEY (user_id) REFERENCES Users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (election_id) REFERENCES Elections(election_id) ON DELETE CASCADE,
    UNIQUE (user_id, election_id) -- Ensure a user is a candidate only once per election
);
GO

-- Votes Table
CREATE TABLE Votes (
    vote_id INT IDENTITY(1,1) PRIMARY KEY,
    voter_id INT NOT NULL,
    candidate_id INT NOT NULL,
    election_id INT NOT NULL,
    vote_time DATETIME DEFAULT GETDATE(),
    FOREIGN KEY (voter_id) REFERENCES Users(user_id) ON DELETE CASCADE,
    FOREIGN KEY (candidate_id) REFERENCES Candidates(candidate_id) ON DELETE CASCADE,
    FOREIGN KEY (election_id) REFERENCES Elections(election_id) ON DELETE CASCADE,
    UNIQUE (voter_id, election_id) -- Ensure one vote per voter per election
);
GO

-- View: Candidate Past Performance
CREATE VIEW CandidatePerformance AS
SELECT 
    c.candidate_id, 
    u.username AS candidate_name, 
    c.party_name, 
    e.election_name, 
    COUNT(v.vote_id) AS total_votes
FROM Candidates c
LEFT JOIN Users u ON c.user_id = u.user_id
LEFT JOIN Elections e ON c.election_id = e.election_id
LEFT JOIN Votes v ON c.candidate_id = v.candidate_id
GROUP BY c.candidate_id, u.username, c.party_name, e.election_name;
GO


-- Insert Dummy Users (Voters and Admins)
INSERT INTO Users (UserID, Name, Age, CNIC, Role, Password)
VALUES
    (1, 'Ali Khan', 25, '42101-1234567-1', 'Voter', 'password123'),
    (2, 'Sara Ahmed', 30, '42201-7654321-2', 'Voter', 'password456'),
    (3, 'Hamza Raza', 35, '42301-9876543-3', 'Admin', 'adminPass'),
    (4, 'Maha Iqbal', 22, '42401-5432109-4', 'Voter', 'voteMaha');

-- Insert Dummy Candidates
INSERT INTO Candidates (CandidateID, Name, Party, ElectionID)
VALUES
    (1, 'Usman Tariq', 'Green Party', 1),
    (2, 'Zainab Noor', 'Justice League', 1),
    (3, 'Farhan Malik', 'Freedom Movement', 2);

-- Insert Dummy Elections
INSERT INTO Elections (ElectionID, Name, StartTime, EndTime, Status)
VALUES
    (1, 'Presidential Election 2025', '2025-04-10 08:00:00', '2025-04-10 18:00:00', 'Upcoming'),
    (2, 'Senate Election 2025', '2025-05-15 09:00:00', '2025-05-15 17:00:00', 'Upcoming');

-- Insert Dummy Votes
INSERT INTO Votes (VoteID, VoterID, CandidateID, ElectionID, Timestamp)
VALUES
    (1, 1, 1, 1, '2025-04-10 10:30:00'),
    (2, 2, 2, 1, '2025-04-10 11:00:00'),
    (3, 4, 1, 1, '2025-04-10 12:15:00');

-- Insert Admin Settings
INSERT INTO AdminSettings (SettingID, ElectionID, StartTime, EndTime, Status)
VALUES
    (1, 1, '2025-04-10 08:00:00', '2025-04-10 18:00:00', 'Scheduled'),
    (2, 2, '2025-05-15 09:00:00', '2025-05-15 17:00:00', 'Scheduled');
