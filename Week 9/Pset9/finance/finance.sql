CREATE TABLE purchases
(
    id        INTEGER PRIMARY KEY,
    user_id   INTEGER,
    symbol    TEXT    NOT NULL,
    name      TEXT    NOT NULL,
    price     REAL    NOT NULL,
    shares    INTEGER NOT NULL,
    total     REAL    NOT NULL,
    timestamp TEXT    NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE ON UPDATE NO ACTION
);
CREATE TABLE sales
(
    id        INTEGER PRIMARY KEY,
    user_id   INTEGER,
    symbol    TEXT    NOT NULL,
    name      TEXT    NOT NULL,
    price     REAL    NOT NULL,
    shares    INTEGER NOT NULL,
    total     REAL    NOT NULL,
    timestamp TEXT    NOT NULL,
    FOREIGN KEY (user_id) REFERENCES users (id) ON DELETE CASCADE ON UPDATE NO ACTION
);

CREATE UNIQUE INDEX idx_purchases_id ON purchases (id);

CREATE INDEX idx_purchases_symbol ON purchases (symbol);
CREATE INDEX idx_purchases_name ON purchases (name);