\name{load}
\alias{load}
\alias{unload}
\title{
  Load/unload the client part of a database interface
}
\description{
Initialize or free the client-side of an R/S database interface
}
\usage{
load(mgr, ...)

unload(mgr, ...)
}
\arguments{
\item{mgr}{
a \code{dbManager} object, as created
through \code{dbManger}
}
\item{\dots }{
any database-specific parameters.
}
}
\value{
NULL
}
\section{Side Effects}{
These functions initialize and release client-part software
of the RS-DBI implementation.
}
\section{References}{
See the Omega Project for Statistical Computing
at \url{http://www.omegahat.org}
for more details on the R/S database interface.
}
\seealso{
On database managers:

\code{\link{dbManager}}
\code{\link{MySQL}}
\code{\link{load}}
\code{\link{unload}}

On connections, SQL statements and resultSets:

\code{\link{dbExecStatement}}
\code{\link{dbExec}}
\code{\link{fetch}}
\code{\link{quickSQL}}

On transaction management:

\code{\link{commit}}
\code{\link{rollback}}

On meta-data:

\code{\link{describe}}
\code{\link{getVersion}}
\code{\link{getDatabases}}
\code{\link{getTables}}
\code{\link{getFields}}
\code{\link{getCurrentDatabase}}
\code{\link{getTableIndices}}
\code{\link{getException}}
\code{\link{getStatement}}
\code{\link{hasCompleted}}
\code{\link{getRowCount}}
\code{\link{getAffectedRows}}
\code{\link{getNullOk}}
\code{\link{getInfo}}
}
\examples{\dontrun{
m <- MySQL()
...
unload(m)
}
}
\keyword{RS-DBI}
\keyword{MySQL}
\keyword{databases}
\keyword{RDBMS}
\keyword{manip}
% docclass is function
% Converted by Sd2Rd version 1.15.2.1.
