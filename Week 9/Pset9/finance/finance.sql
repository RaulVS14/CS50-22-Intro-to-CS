CREATE TABLE transactions
(
    id        INTEGER PRIMARY KEY,
    user_id   INTEGER,
    symbol    TEXT    NOT NULL,
    price     REAL    NOT NULL,
    shares    INTEGER NOT NULL,
    type      TEXT    NOT NULL,
    timestamp TEXT    NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE TABLE user_shares
(
    id      INTEGER PRIMARY KEY,
    user_id INTEGER,
    symbol  TEXT    NOT NULL,
    name    TEXT    NOT NULL,
    shares  INTEGER NOT NULL,
    UNIQUE (user_id, symbol),
    FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE UNIQUE INDEX idx_transactions_id ON transactions (id);
CREATE INDEX idx_transactions_symbol ON transactions (symbol);
CREATE INDEX idx_transactions_user_id ON transactions (user_id);